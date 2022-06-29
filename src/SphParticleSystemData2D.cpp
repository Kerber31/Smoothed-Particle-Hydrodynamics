/**
 * @file SphParticleSystemData2D.cpp
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Implementation of the particle system data for 2D SPH simulators.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#include "../include/SphParticleSystemData2D.h"
#include "../include/SphKernels.h"
#include "../include/Constants.h"

SphParticleSystemData2D::SphParticleSystemData2D() {}

SphParticleSystemData2D::~SphParticleSystemData2D() {}

void SphParticleSystemData2D::addParticle(Eigen::Vector2d positon) {
    _positions.push_back(positon);
    _velocities.push_back(Eigen::Vector2d(0, 0));
    _forces.push_back(Eigen::Vector2d(0, 0));
    _densities.push_back(0);
    _pressures.push_back(0);
    numberOfParticles++;
}

void SphParticleSystemData2D::computeDensityPressure() {
    SphPoly6Kernel kernel(_kernelRadius);

    #pragma omp parallel for
    for (size_t i = 0; i < numberOfParticles; i++) {
        _densities[i] = 0;
        for (size_t j = 0; j < numberOfParticles; j++) {
            Eigen::Vector2d resultingVector = _positions[j] - _positions[i];
			float distanceSquared = resultingVector.squaredNorm();

            if (distanceSquared < _kernelRadiusSquared)
			{
				_densities[i] += _mass * kernel(_kernelRadiusSquared - distanceSquared);
			}
        }
        _pressures[i] = GAS_CONSTANT * (_densities[i] - REST_DENSITY);
    }
}

std::vector<Eigen::Vector2d>& SphParticleSystemData2D::getPositions() {
    return _positions;
}

std::vector<Eigen::Vector2d>& SphParticleSystemData2D::getVelocities() {
    return _velocities;
}

std::vector<Eigen::Vector2d>& SphParticleSystemData2D::getForces() {
    return _forces;
}

std::vector<double>& SphParticleSystemData2D::getDensities() {
    return _densities;
}

std::vector<double>& SphParticleSystemData2D::getPressures() {
    return _pressures;
}

const double SphParticleSystemData2D::getKernelRadius() {
    return _kernelRadius;
}

void SphParticleSystemData2D::setKernelRadius(double newKernelRadius) {
    _kernelRadius = newKernelRadius;
    _kernelRadiusSquared = newKernelRadius * newKernelRadius;
}

const double SphParticleSystemData2D::getMass() {
    return _mass;
}

void SphParticleSystemData2D::setMass(double newMass) {
    _mass = newMass;
}

const double SphParticleSystemData2D::getViscosityConstant() {
   return _viscosityConstant; 
}

void SphParticleSystemData2D::setViscosityConstant(double newViscosityConstant) {
    _viscosityConstant = newViscosityConstant;
}

void SphParticleSystemData2D::setParticleRadius(double newParticleRadius) {
    _particleRadius = newParticleRadius;    
}

const double SphParticleSystemData2D::getParticleRadius() {
    return _particleRadius;
}

void SphParticleSystemData2D::buildNeighborhood() {
    _neighborhood->build(_positions);
}

std::vector<Eigen::Vector2d>& SphParticleSystemData2D::getLastPositions() {
    return _lastPositions;
}

std::vector<Eigen::Vector2d>& SphParticleSystemData2D::getProjectedPositions() {
    return _projectedPositions;
}

std::vector<double>& SphParticleSystemData2D::getDensityVariations() {
    return _densityVariations;
}

std::vector<double>& SphParticleSystemData2D::getPressureVariations() {
    return _pressureVariations;
}

double SphParticleSystemData2D::getKernelFactor() {
    return _kernelFactor;
}

double SphParticleSystemData2D::getKernelFactorNorm() {
    return _kernelFactorNorm;
}

double SphParticleSystemData2D::getStiffness() {
    return _stiffness;
}

double SphParticleSystemData2D::getStiffnessAtProximity() {
    return _stiffnessAtProximity;
}

double SphParticleSystemData2D::getLinearViscosity() {
    return _linearViscosity;
}

double SphParticleSystemData2D::getQuadraticViscosity() {
    return _quadraticViscosity;
}

double SphParticleSystemData2D::getSurfaceTension() {
    return _surfaceTension;
}  

ParticleNeighborhood2DPtr SphParticleSystemData2D::getNeighborhood() {
    return _neighborhood;
}