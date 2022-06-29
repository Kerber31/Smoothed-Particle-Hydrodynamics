/**
 * @file VSphParticleSystemData2D.h
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Header of the Viscoelastic SPH particle system data for 2D systems.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#ifndef VSPHPARTICLESYSTEMDATA2D_H
#define VSPHPARTICLESYSTEMDATA2D_H

#include "SphParticleSystemData2D.h"
#include <memory>

/**
 * @brief Class that implements the Viscoelastic SPH particle system data for 2D systems.
 * 
 */
class VSphParticleSystemData2D: public SphParticleSystemData2D { 
public:
    /**
     * @brief Default constructor for VSphParticleSystemData2D.
     * 
     */
    VSphParticleSystemData2D();

    /**
     * @brief Destructor for VSphParticleSystemData2D.
     * 
     */
    ~VSphParticleSystemData2D();

    /**
     * @brief Compute density and pressure for each particle in 
     * the system, as well as their variatinos.
     * 
     */
    void computeDensityPressure() override;

    /**
     * @brief Adds a new particle to the system with given position parameter.
     * 
     * @param positon: the position of the particle to be added.
     */
    void addParticle(Eigen::Vector2d positon) override;
};

/**
 * @brief std::shared_ptr for VSphParticleSystemData2D.
 * 
 */
typedef std::shared_ptr<VSphParticleSystemData2D> VSphParticleSystemData2DPtr;

#endif