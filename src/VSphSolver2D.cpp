/**
 * @file VSphSolver2D.cpp
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Implementation of the Viscoelastic SPH particle system solver for 2D systems.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#include "../include/VSphSolver2D.h"
#include "../include/ParticleNeighborhood2D.h" 
#include "../include/VSphParticleSystemData2D.h"
#include "../include/Constants.h"
#include <memory>

VSphSolver2D::VSphSolver2D() : SphSolver2D() {}

VSphSolver2D::~VSphSolver2D() {}

VSphSolver2D::VSphSolver2D(int numberOfParticles_, std::string fileName) : SphSolver2D(fileName) {
    _viewWidth = 12.5;
    _viewHeight = _windowHeight * _viewWidth / _windowWidth;

    _fileName = fileName;

    _boundaries[2] = Eigen::Vector3d(-1, 0, -_viewWidth);
	_boundaries[3] = Eigen::Vector3d(0, -1, -_viewHeight);

    _timeStepSizeInSeconds = ((1.0 / _fps) / _solverSteps);
    _timeStepSizeInSecondsSquared = _timeStepSizeInSeconds * _timeStepSizeInSeconds;

    _particleSystemData = std::make_shared<VSphParticleSystemData2D>();

    auto particleRadius = _particleSystemData->getParticleRadius();
    auto kernelRadius = _particleSystemData->getKernelRadius();

	Eigen::Vector2d start(0.25f * _viewWidth, 0.5f * _viewHeight);
	double x0 = start(0);
	int num = sqrt(numberOfParticles_);
	double spacing = particleRadius;
    std::vector<Eigen::Vector2d> positions = {};

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			positions.push_back(start);
            _particleSystemData->addParticle(start);
			start(0) += 2.0 * particleRadius + spacing;
		}
		start(0) = x0;
		start(1) -= 2.0 * particleRadius + spacing;
	}

    _particleSystemData->getNeighborhood()->setGridResolution(_viewWidth, _viewHeight, kernelRadius);
	_particleSystemData->getNeighborhood()->build(positions);

    _pointSize = 2.5f * getParticleRadius() * _windowWidth / _viewHeight; 

    _boundaryDumping = 0.5;
}


void VSphSolver2D::applyExternalForces() {
    auto& velocities = _particleSystemData->getVelocities();

    #pragma omp parallel for
	for (int i = 0; i < _particleSystemData->numberOfParticles; i++) {
		velocities[i] += _timeStepSizeInSeconds * G2D;
	}
}

void VSphSolver2D::integrate() {
    auto& positions = _particleSystemData->getPositions();
    auto& velocities = _particleSystemData->getVelocities();
    auto& lastPositions = _particleSystemData->getLastPositions();

    #pragma omp parallel for
	for (int i = 0; i < _particleSystemData->numberOfParticles; i++) {
		lastPositions[i] = positions[i];
		positions[i] += _timeStepSizeInSeconds * velocities[i];
	}
}

void VSphSolver2D::project() {
    auto& positions = _particleSystemData->getPositions();
    auto& velocities = _particleSystemData->getVelocities();
    auto& densities = _particleSystemData->getDensities();
    auto& pressures = _particleSystemData->getPressures();
    auto& projectedPositions = _particleSystemData->getProjectedPositions();
    auto& pressureVariations = _particleSystemData->getPressureVariations();
    auto& densitVariations = _particleSystemData->getDensityVariations();
    auto& lastPositions = _particleSystemData->getProjectedPositions();
    auto kernelFactor = _particleSystemData->getKernelFactor();
    auto kernelFactorNorm = _particleSystemData->getKernelFactorNorm();
    auto neighborhood = _particleSystemData->getNeighborhood();
    auto kernelRadius = _particleSystemData->getKernelRadius();
    auto mass = _particleSystemData->getMass();
    auto surfaceTension = _particleSystemData->getSurfaceTension();
    auto linearViscosity = _particleSystemData->getLinearViscosity();
    auto quadraticViscosity = _particleSystemData->getQuadraticViscosity();

    #pragma omp parallel for
	for (int i = 0; i < _particleSystemData->numberOfParticles; i++)
	{
		Eigen::Vector2d projectedPosition = positions[i];
        // auto distances = neighborhood->getDistances(i);

        neighborhood->forEachNearbyPoint(i, 
            [&](int j, double distance) {
                double r = distance;
                Eigen::Vector2d dx = positions[j] - positions[i];

                double a = 1. - r / kernelRadius;
                double d = _timeStepSizeInSecondsSquared *
                             ((pressureVariations[i] + pressureVariations[j])
                              * a * a * a * kernelFactorNorm + (pressures[i] + pressures[j])
                               * a * a * kernelFactor) / 2.;

                // relaxation
                projectedPosition -= d * dx / (r * mass);

                projectedPosition += (surfaceTension / mass) * mass * a * a * kernelFactor * dx;

                // linear and quadratic visc
                Eigen::Vector2d dv = velocities[i] - velocities[j];
                double u = dv.dot(dx);
                if (u > 0) {
                    u /= r;
                    double a = 1 - r / kernelRadius;
                    double I = 0.5 * _timeStepSizeInSeconds * a * (linearViscosity * u + quadraticViscosity * u * u);
                    projectedPosition -= I * dx * _timeStepSizeInSeconds;
                }
            }
        );

		projectedPositions[i] = projectedPosition;
	}
}

void VSphSolver2D::correct() {
    auto& positions = _particleSystemData->getPositions();
    auto& velocities = _particleSystemData->getVelocities();
    auto& projectedPositions = _particleSystemData->getProjectedPositions();
    auto& lastPositions = _particleSystemData->getLastPositions();

    #pragma omp parallel for
	for (int i = 0; i < _particleSystemData->numberOfParticles; i++) {
		positions[i] = projectedPositions[i];
		velocities[i] = (positions[i] - lastPositions[i]) / _timeStepSizeInSeconds;
	}
}

void VSphSolver2D::update() {
    ParticleNeighborhood2DPtr neighorhood = _particleSystemData->getNeighborhood();
    auto& positions = _particleSystemData->getPositions();

    for (int i = 0; i < _solverSteps; i++) {
		applyExternalForces();
		integrate();
		neighorhood->build(positions);
		_particleSystemData->computeDensityPressure();
		project();
		correct();
		enforceBoundary();
    }

    if (_fileName != "") {
        writeToFile();
    }
}