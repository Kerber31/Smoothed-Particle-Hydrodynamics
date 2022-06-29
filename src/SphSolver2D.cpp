/**
 * @file SphSolver2D.cpp
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Implementatio of the base SPH solver for 2D particle systems.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#include "../include/Constants.h"
#include "../include/SphKernels.h"
#include "../include/SphSolver2D.h"
#include <eigen3/Eigen/Dense>
#include <string>
#include <iomanip>
#include <sstream>

SphSolver2D::SphSolver2D(std::string fileName) {
    _boundaries.push_back(Eigen::Vector3d(1, 0, 0));
	_boundaries.push_back(Eigen::Vector3d(0, 1, 0));
	_boundaries.push_back(Eigen::Vector3d(-1, 0, -_viewWidth));
	_boundaries.push_back(Eigen::Vector3d(0, -1, -_viewHeight));

    _fileName = fileName;

    if (fileName != "") {
        _csv.eraseFileContents(_fileName);
    }
}

SphSolver2D::~SphSolver2D() {}

SphSolver2D::SphSolver2D(int numberOfParticles, std::string fileName) {
    _boundaryDumping = 1.0;
    _fileName = fileName;
    
    if (fileName != "") {
        _csv.eraseFileContents(_fileName);
    }

    _boundaries.push_back(Eigen::Vector3d(1, 0, 0));
	_boundaries.push_back(Eigen::Vector3d(0, 1, 0));
	_boundaries.push_back(Eigen::Vector3d(-1, 0, -_viewWidth));
	_boundaries.push_back(Eigen::Vector3d(0, -1, -_viewHeight));

    _particleSystemData = std::make_shared<SphParticleSystemData2D>(); 
    double kernelRadius = _particleSystemData->getKernelRadius();
    int count = 0;

    _pointSize = getKernelRadius() / 2.0;

	for (double y = kernelRadius; y < _viewHeight - kernelRadius * 2.f; y += kernelRadius) {
		for (double x = _viewWidth / 4; x <= _viewWidth / 2; x += kernelRadius) {
            if (count == numberOfParticles) {
                return;
            }

            float jitter = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            Eigen::Vector2d position = Eigen::Vector2d(x + jitter, y + jitter);
            addParticle(position);
            count++;
		}
	}
}

void SphSolver2D::addParticle(Eigen::Vector2d positon) {
    _particleSystemData->addParticle(positon);
}

std::vector<Eigen::Vector2d>& SphSolver2D::getPositions() {
    return _particleSystemData->getPositions(); 
}

void SphSolver2D::update() {
    _particleSystemData->computeDensityPressure();
    computeForces();
    integrate();
    enforceBoundary();

    if (_fileName != "") {
        writeToFile();
    }
}

void SphSolver2D::writeToFile() {

    auto& positions = _particleSystemData->getPositions();

	for (int i = 0; i < positions.size(); ++i) {
        // Create an output string stream
        std::ostringstream x;
        std::ostringstream y;
        // Set Fixed -Point Notation
        x << std::fixed;
        y << std::fixed;
        // Set precision to 2 digits
        x << std::setprecision(10);
        y << std::setprecision(10);
        //Add double to stream
        x << positions[i](0);
        y << positions[i](1);
        // Get string from output string stream
        std::string x_str = x.str();
        std::string y_str = y.str();

        std::string s = x_str + " " + y_str;
		_csv << s;
	}

	_csv.writeToFile(_fileName, true);
	_csv.resetContent();
}

void SphSolver2D::computeForces() {
    size_t numberOfParticles = _particleSystemData->numberOfParticles;
    std::vector<Eigen::Vector2d>& positions = _particleSystemData->getPositions();
    std::vector<Eigen::Vector2d>& velocities = _particleSystemData->getVelocities();
    std::vector<Eigen::Vector2d>& forces = _particleSystemData->getForces();
    std::vector<double>& pressures = _particleSystemData->getPressures();
    std::vector<double>& densities = _particleSystemData->getDensities();
    double kernelRadius = _particleSystemData->getKernelRadius();
    double mass = _particleSystemData->getMass();
    double viscosityConstant = _particleSystemData->getViscosityConstant();
    SphViscosityKernel viscosityKernel(kernelRadius);
    SphSpikyKernel spikyKernel(kernelRadius);

    // #pragma omp parallel for
    for (size_t i = 0; i < numberOfParticles; i++) {
        Eigen::Vector2d fpress(0.0, 0.0);
        Eigen::Vector2d fvisc(0.0, 0.0);

        for (size_t j = 0; j < numberOfParticles; j++) {
			if (i == j) {
				continue;
			}
            
			Eigen::Vector2d resultingVector = positions[j] - positions[i];
			float distance = resultingVector.norm();

            if (distance < kernelRadius) {
				// compute pressure force contribution
				fpress += -resultingVector.normalized() * mass * (pressures[i] + pressures[j]) / 
                            (2.0 * densities[j]) * spikyKernel.gradientAt(kernelRadius - distance);
				// compute viscosity force contribution
				fvisc += viscosityConstant * mass * (velocities[j] - velocities[i]) / 
                            densities[j] * viscosityKernel.laplacianAt(kernelRadius - distance);
			}
		}

        Eigen::Vector2d fgrav = G2D * mass / densities[i];
		forces[i] = fpress + fvisc + fgrav;
	}
}

void SphSolver2D::enforceBoundary() {
    size_t numberOfParticles = _particleSystemData->numberOfParticles;
    std::vector<Eigen::Vector2d>& positions = _particleSystemData->getPositions();
    std::vector<Eigen::Vector2d>& velocities = _particleSystemData->getVelocities();
    double particleRadius = _particleSystemData->getParticleRadius();
    
    #pragma omp parallel for
	for (size_t i = 0; i < numberOfParticles; i++) {
		for (auto b : _boundaries) {
			double d = positions[i](0) * b(0) + positions[i](1) * b(1) - b(2);
			if ((d = std::max(0., d)) < particleRadius){
				velocities[i] += (particleRadius - d) * b.segment<2>(0) / _timeStepSizeInSeconds;
                velocities[i] *= _boundaryDumping;
            }
		}
    }
}

void SphSolver2D::integrate() {
    size_t numberOfParticles = _particleSystemData->numberOfParticles;
    std::vector<Eigen::Vector2d>& positions = _particleSystemData->getPositions();
    std::vector<Eigen::Vector2d>& velocities = _particleSystemData->getVelocities();
    std::vector<Eigen::Vector2d>& forces = _particleSystemData->getForces();
    std::vector<double>& densities = _particleSystemData->getDensities();
    std::vector<double>& pressures = _particleSystemData->getPressures();
    double kernelRadius = _particleSystemData->getKernelRadius(); 

    #pragma omp parallel for
    for (size_t i = 0; i < numberOfParticles; i++) {
        velocities[i] += (forces[i] / densities[i]) * _timeStepSizeInSeconds;
        positions[i] += velocities[i] * _timeStepSizeInSeconds;
    }
}

double SphSolver2D::getKernelRadius() {
    return _particleSystemData->getKernelRadius();
}

double SphSolver2D::getParticleRadius() {
    return _particleSystemData->getParticleRadius();
}

double SphSolver2D::getViewHeight() {
    return _viewHeight;
}

double SphSolver2D::getViewWidth() {
    return _viewWidth;
}

double SphSolver2D::getPointSize() {
    return _pointSize;
}

int SphSolver2D::getWindowWidth() {
    return _windowWidth;
}

int SphSolver2D::getWindowHeight() {
    return _windowHeight;
}