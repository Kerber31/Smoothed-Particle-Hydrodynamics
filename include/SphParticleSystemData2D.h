/**
 * @file SphParticleSystemData2D.h
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Header of the particle system data for 2D SPH simulators.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#ifndef SPHPARTICLESYSTEMDATA2D_H
#define SPHPARTICLESYSTEMDATA2D_H

#include "ParticleNeighborhood2D.h"
#include <eigen3/Eigen/Dense>
#include <memory>
#include <vector>

/**
 * @brief Class that handles data for 2D SPH system solvers.
 */
class SphParticleSystemData2D {
public:
    
    /**
     * @brief Variable that stores the number of particles
     * on the system.
     */
    size_t numberOfParticles = 0;
    
    /**
     * @brief Class default initializer.
     */
    SphParticleSystemData2D();

    /**
     * @brief Class default destroyer.
     */
    ~SphParticleSystemData2D();
    
    /**
     * @brief This method adds a particle to the system. Can be overrided.
     *
     * @param position: Eigen::Vector2d representing the new particle's 
     *		     position.
     */
    virtual void addParticle(Eigen::Vector2d positon);

    /**
     * @brief This method computes the density and pressure of the particles
     * for a solver time step. Can be overrided.
     */
    virtual void computeDensityPressure();

    /**
     * @brief This method returns the positions of the particles
     * in the system, in order.
     *
     * @returns A list of particle positions of type 
     *      std::vector < Eigen::Vector2d >&.
     */
    std::vector<Eigen::Vector2d>& getPositions();

    /**
     * @brief This method returns the velocities of the particles
     * in the system, in order.
     * 
     * @returns A list of particle velocities of type
     *    std::vector < Eigen::Vector2d >&.
     */
    std::vector<Eigen::Vector2d>& getVelocities();

    /** 
     * @brief This method returns the forces over each particle
     * in the system, in order.
     * 
     * @returns A list of particle forces of type
     *    std::vector < Eigen::Vector2d >&.
     */
    std::vector<Eigen::Vector2d>& getForces();

    /**
     * @brief This method returns the densities of the particles
     * in the system, in order.
     * 
     * @returns A list of particle densities of type
     *    std::vector < double >&.
     */
    std::vector<double>& getDensities();

    /**
     * @brief This method returns the pressures of the particles
     * in the system, in order.
     * 
     * @returns A list of particle pressures of type
     *    std::vector < double >&.
     */
    std::vector<double>& getPressures();

    /**
     * @brief This method returns the kernel radius of the system.
     * 
     * @returns Kernel radius of type double.       
     */
    const double getKernelRadius();

    /**
     * @brief This method sets a new kernel radius for the system.
     * 
     * @param newKernelRadius: double representing the new kernel radius.       
     */
    void setKernelRadius(double newKernelRadius);

    /**
     * @brief This method returns the mass of the particles in the system.
     * 
     * @returns A constant double representing the mass of the particles. 
     */
    const double getMass();

    /**
     * @brief Sets a new mass for the particles in the system.
     * 
     * @param newMass: double representing the new mass.
     */
    void setMass(double newMass);

    /**
     * @brief Set a new vistosity constant to the system.
     * 
     * @param newViscosityConstant: double representing the new viscosity constant. 
     */
    void setViscosityConstant(double newViscosityConstant);

    /**
     * @brief This method returns the viscosity constant of the system.
     * 
     * @return Viscosity constant of type const double. 
     */
    const double getViscosityConstant();

    /**
     * @brief Set a new particle radius to the system.
     * 
     * @param newParticleRadius: double representing the new particle radius.
     */
    void setParticleRadius(double newParticleRadius);

    /**
     * @brief Get the particle radius of the system.
     * 
     * @return const double representing the particle radius.
     */
    const double getParticleRadius();

    /**
     * @brief builds the neighborhood structure for the system.
     */
    void buildNeighborhood();

    /**
     * @brief Get the Neighborhood object
     * 
     * @return ParticleNeighborhood2DPtr representing the neighborhood structure.
     */
    ParticleNeighborhood2DPtr getNeighborhood();

    /**
     * @brief Get the density variation for each particle in the system, in order.
     * 
     * @return std::vector<double>&  representing the density variations.
     */
    std::vector<double>& getDensityVariations();

    /**
     * @brief Get the pressure variation for each particle in the system, in order.
     * 
     * @return std::vector<double>&  representing the pressure variations.
     */
    std::vector<double>& getPressureVariations();

    /**
     * @brief Get the last position of each particle in the system, in order.
     * 
     * @return std::vector< Eigen::Vector2d >&  representing the last positions.
     */   
    std::vector<Eigen::Vector2d>& getLastPositions();

    /**
     * @brief Get the projected porition of each particle in the system, in order.
     * 
     * @return std::vector< Eigen::Vector2d >&  representing the projected poritions.
     */  
    std::vector<Eigen::Vector2d>& getProjectedPositions();
    
    /**
     * @brief Get the kernelFactor constant.
     * 
     * @return double representing the kernel factor.
     */
    double getKernelFactor();

    /**
     * @brief Get the kernelFactorNorm constant.
     * 
     * @return double representing the kernelFactorNorm.
     */
    double getKernelFactorNorm();

    /**
     * @brief Get the stiffness constant.
     * 
     * @return double reppresenting the stiffness of the system.
     */
    double getStiffness();
    double getStiffnessAtProximity();

    /**
     * @brief Get the linearViscosity constant.
     * 
     * @return double representing the linear viscosity of the system.
     */
    double getLinearViscosity();

    /**
     * @brief Get the quadraticViscosity constant.
     * 
     * @return double representing the quadratic viscosity of the system.
     */
    double getQuadraticViscosity();

    /**
     * @brief Get the surface tension constant
     * 
     * @return double reppresenting the surface tension of the system.  
     */
    double getSurfaceTension();
    
protected:

    /**
     * @brief std::shared_ptr to the neighborhood structure.
     * 
     */
    ParticleNeighborhood2DPtr _neighborhood;

    /**
     * @brief vector of particle positions.
     * 
     */
    std::vector<Eigen::Vector2d> _positions = {};

    /**
     * @brief vector of particle velocities.
     * 
     */
    std::vector<Eigen::Vector2d> _velocities = {};

    /**
     * @brief vector of forces over each particle.
     * 
     */
    std::vector<Eigen::Vector2d> _forces = {};

    /**
     * @brief vector of the densities of each particle.
     * 
     */
    std::vector<double> _densities = {};

    /**
     * @brief vector of the pressures of each particle.
     * 
     */
    std::vector<double> _pressures = {};

    /**
     * @brief vector of the last positions of each particle.
     * 
     */
    std::vector<Eigen::Vector2d> _lastPositions = {};

    /**
     * @brief vector of the projected prositions of each particle.
     * 
     */
    std::vector<Eigen::Vector2d> _projectedPositions = {};
    
    /**
     * @brief vector of the density variations of each particle.
     * 
     */
    std::vector<double> _densityVariations = {};

    /**
     * @brief vector of the pressure variations of each particle.
     * 
     */
    std::vector<double> _pressureVariations = {};

    /**
     * @brief Kernel factor constat.
     * 
     */
    double _kernelFactor;

    /**
     * @brief Kernel factors norm constant.
     * 
     */
    double _kernelFactorNorm;

    /**
     * @brief Stiffnesses constant.
     * 
     */
    double _stiffness = 0.08;

    /**
     * @brief Stiffnesses at proximity constant.
     * 
     */
    double _stiffnessAtProximity = 0.1;

    /**
     * @brief Linear viscosity constant.
     * 
     */
    double _linearViscosity = 0.25;

    /**
     * @brief Quadratic viscosity constant.
     * 
     */
    double _quadraticViscosity = 0.5;

    /**
     * @brief Surface tension constant.
     * 
     */
    double _surfaceTension = 0.0001;

    /**
     * @brief Kernel radius constant.
     * 
     */
    double _kernelRadius = 16.0;

    /**
     * @brief Kernel radius squared constant.
     * 
     */
    double _kernelRadiusSquared = 16.0*16.0;

    /**
     * @brief Mass of the system.
     * 
     */
    double _mass = 2.5;

    /**
     * @brief Viscosity constant.
     * 
     */
    double _viscosityConstant = 200.0;

    /**
     * @brief Particle radius constant.
     * 
     */
    double _particleRadius = 16.0;
};

/**
 * @brief std::shared_ptr to SphParticleSystemData2D.
 *  
 */
typedef std::shared_ptr<SphParticleSystemData2D> SphParticleSystemData2DPtr;    

#endif
