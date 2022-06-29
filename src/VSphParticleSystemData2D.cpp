/**
 * @file VSphParticleSystemData2D.cpp
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Implementation of the Viscoelastic SPH particle system data for 2D systems.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#include "../include/VSphParticleSystemData2D.h"
#include "../include/GridNeighborhood2D.h" 
#include "../include/Constants.h"
#include <memory>

VSphParticleSystemData2D::VSphParticleSystemData2D() : SphParticleSystemData2D() {
    _particleRadius = 0.03;
    _kernelRadius = 6.0 * _particleRadius;
    _kernelFactor = 20. / (2. * M_PI * _kernelRadius * _kernelRadius);
    _kernelFactorNorm = 30. / (2. * M_PI * _kernelRadius * _kernelRadius);
    _mass = 1.0;

    _neighborhood = std::make_shared<GridNeighborhood2D>();
}

VSphParticleSystemData2D::~VSphParticleSystemData2D() {}

void VSphParticleSystemData2D::addParticle(Eigen::Vector2d positon) {
    SphParticleSystemData2D::addParticle(positon);
    _projectedPositions.push_back(Eigen::Vector2d(0.0, 0.0));
    _densityVariations.push_back(0.0);
    _pressureVariations.push_back(0.0);
    _lastPositions.push_back(positon);
}

void VSphParticleSystemData2D::computeDensityPressure() {
    #pragma omp parallel for
    for (int i = 0; i < numberOfParticles; i++) {
        _densities[i] = 0.0;
        _densityVariations[i] = 0.0;

        _neighborhood->forEachNearbyPoint(i, 
            [&](int j, double distance) {
                double a = 1. - distance / _kernelRadius;
                _densities[i] += _mass * a * a * a * _kernelFactor;
                _densityVariations[i] += _mass * a * a * a * a * _kernelFactorNorm;
            }
        );

        _pressures[i] = _stiffness * (_densities[i] - _mass * ELASTIC_REST_DENSITY);
        _pressureVariations[i] = _stiffnessAtProximity * _densityVariations[i];
    }
}