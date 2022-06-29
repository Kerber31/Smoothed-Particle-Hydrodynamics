/**
 * @file VSphSolver2D.h
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Header of the Viscoelastic SPH particle system solver for 2D systems.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#ifndef VSPHSOLVER2D_H
#define VSPHSOLVER2D_H

#include "SphSolver2D.h"
#include <eigen3/Eigen/Dense>

/**
 * @brief Class that implemets the Viscoelastic SPH particle system solver for 2D systems.
 * 
 */
class VSphSolver2D : public SphSolver2D
{ 
public:

    /**
     * @brief Default constructor for VSphSolver2D.
     * 
     */
    VSphSolver2D();

    /**
     * @brief Destructor for VSphSolver2D.
     * 
     */ 
    ~VSphSolver2D();

    /**
     * @brief Construct a new VSphSolver2D object with a given number of particles.
     * 
     * @param numberOfParticles: Number of particles to added to the system. 
     */
    VSphSolver2D(int numberOfParticles, std::string fileName = "");

    /**
     * @brief Perform one time step for the system, updating the parameters of each aprticle. 
     * 
     */
    void update() override;

private:

    /**
     * @brief Number of substeps to perform in each time step.
     * 
     */
    int _solverSteps = 10;

    /**
     * @brief Expected frames per second for the simulation.
     * 
     */
    int _fps = 30;
    
    /**
     * @brief double representing the time step size in seconds square for the simulation.
     * 
     */
    double _timeStepSizeInSecondsSquared = 1.0;

    /**
     * @brief Apply external forces on each particle.
     * 
     */
    void applyExternalForces();

    /**
     * @brief Project the particle positions and velocities for the next time step.
     * 
     */
    void project();

    /**
     * @brief Correct the positions and velocities to enforce fluid incompressibility.
     * 
     */
    void correct();

    /**
     * @brief Perform the integration timestep for each particle in the system.
     * 
     */
    void integrate();
};

/**
 * @brief std::shared_ptr for VSphSolver2D.
 * 
 */
typedef std::shared_ptr<VSphSolver2D> VSphSolver2DPtr;

#endif