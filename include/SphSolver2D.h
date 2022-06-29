/**
 * @file SphSolver2D.h
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Header of the base SPH solver for 2D particle systems.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#ifndef SPHSOLVER2D_H 
#define SPHSOLVER2D_H

#include "SphParticleSystemData2D.h"
#include "CsvWriter.h"
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <typeinfo>
#include <regex>
#include <eigen3/Eigen/Dense>

/**
 * @brief Class that implements the base SPH solver for 2D pparticle systems.
 * 
 */
class SphSolver2D {
public:

    /**
     * @brief Default constructor for SphSolver2D.
     * 
     */
    SphSolver2D(std::string fileName = "");

    /**
     * @brief Destructor for SphSolver2D.
     * 
     */
    ~SphSolver2D();

    /**
     * @brief Construct a new SphSolver2D object with a given number of particles.
     * 
     * @param numberOfParticles: Number of particles to added to the system. 
     */
    SphSolver2D(int numberOfParticles, std::string fileName = "");

    /**
     * @brief Add a new particle to the system with given position parameter.
     * 
     * @param positon: Position of the particle to be added. 
     */
    void addParticle(Eigen::Vector2d positon);

    /**
     * @brief Get the positions of each particle, in order.
     * 
     * @return std::vector< Eigen::Vector2d >& representing the positions of each particle.  
     */
    std::vector<Eigen::Vector2d>& getPositions();
    
    /**
     * @brief Perform one time step for the system, updating the parameters of each aprticle.
     * Can be overrided. 
     * 
     */
    virtual void update();

    /**
     * @brief Get the kernel radius constat.
     * 
     * @return double representing the kernel radius constat.
     */
    double getKernelRadius();

    /**
     * @brief Get the particle radius constant.
     * 
     * @return double representing the particle radius constant.
     */
    double getParticleRadius();

    /**
     * @brief Get the height of the view.
     * 
     * @return doule representing height of the view.
     */
    double getViewHeight();

    /**
     * @brief Get the width of the view.
     * 
     * @return doule representing height of the view. 
     */
    double getViewWidth();

    /**
     * @brief Get the Window Width for rendering.
     * 
     * @return int representing the window width. 
     */
    int getWindowWidth();

    /**
     * @brief Get the Window Height for rendering.
     * 
     * @return int representing the window height.
     */
    int getWindowHeight();

    /**
     * @brief Get the size of points to be rendered.
     * 
     * @return double representing the size of the points.
     */
    double getPointSize();

protected:

    /**
     * @brief st::shared_ptr representing the particle system data.
     * 
     */
    SphParticleSystemData2DPtr _particleSystemData;

    /**
     * @brief CsvWriter object to write the data to a csv file.
     * 
     */
    CsvWriter _csv;

    /**
     * @brief vector of boundary conditions.
     * 
     */
    std::vector<Eigen::Vector3d> _boundaries = std::vector<Eigen::Vector3d>();

    /**
     * @brief double representing the time ste size in seconds.
     * 
     */
    double _timeStepSizeInSeconds = 0.0007;

    /**
     * @brief double representing the boundary dumping constant.
     * 
     */
    double _boundaryDumping = -0.5;

    /**
     * @brief int representing the width of the screen in pixels.
     * 
     */
    int _windowWidth = 800;

    /**
     * @brief int representing the height of the screen in pixels.
     * 
     */
    int _windowHeight = 600;

    /**
     * @brief Width of the simulation view.
     * 
     */
    double _viewWidth = 1.5 * 800.0;

    /**
     * @brief Height of the simulation view.
     * 
     */
    double _viewHeight = 1.5 * 600.0;

    /**
     * @brief double representing the size of the points to be rendered.
     * 
     */
    double _pointSize = 1.0;

    /**
     * @brief String representing the name of the file to write the simulation data to.
     * 
     */
    std::string _fileName = "";

    /**
     * @brief Compute the forces over each particle during one time step.
     * 
     */
    void computeForces();

    /**
     * @brief Perform the integration step for each particle during one time step.
     * 
     */
    void integrate();

    /**
     * @brief Enforce the boundary conditions for each particle.
     * 
     */
    void enforceBoundary();

    /**
     * @brief Write possitions to file.
     * 
     * @param filename: string representing the file's name.
     */
    void writeToFile();
};

/**
 * @brief std::shared_ptr for SphSolver2D.
 * 
 */
typedef std::shared_ptr<SphSolver2D> SphSolver2DPtr;

#endif