/**
 * @file GridNeighborhood2D.h
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Header of the Grid Neighborhood for 2D particle systems.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#ifndef GRIDNEIGHBORHOOD_H
#define GRIDNEIGHBORHOOD_H

#include <vector>
#include <memory>
#include <eigen3/Eigen/Dense>
#include "ParticleNeighborhood2D.h"

/**
 * @brief Struct describing a neighbor linked list.
 * 
 */
struct Neighbor {
public:

    /**
     * @brief Constructs a new Neighbor with given index.
     * 
     * @param index_: Index of the neighbor on the ParticleSystemData
     *  class's list of particles.
     */
    Neighbor(int index_) : index(index_) {}
    
    /**
     * @brief Index of the neighbor on the ParticleSystemData 
     * class's list of particles.
     * 
     */
    int index;

    /**
     * @brief Next neighbor in the liked list.
     * 
     */
    Neighbor *next = nullptr;
};

/**
 * @brief Struct describing the neighborhood of a particle.
 * 
 */
struct Neighborhood {
public:

    /**
     * @brief Default costructor of the Neighborhood struct.
     * 
     */
	Neighborhood() : neighbors(MAX_NEIGHBORS), distances(MAX_NEIGHBORS), numNeighbors(0) {}

    /**
     * @brief List of neighbors of the particle.
     * 
     */
	std::vector<const Neighbor *> neighbors;

    /**
     * @brief The distance to each neighbor on the neighbors list.
     * 
     */
	std::vector<double> distances;

    /**
     * @brief Number of neighbors of the particle.
     * 
     */
	int numNeighbors;

    /**
     * @brief Maximum number of neighbors for a particle.
     * 
     */
	const static int MAX_NEIGHBORS = 64;
};

/**
 * @brief Class describing the Grid Neighborhood for 2D particle systems.
 * 
 */
class GridNeighborhood2D: public ParticleNeighborhood2D {
public:

    /**
     * @brief Default constructor for the GridNeighborhood2D class.
     * 
     */
    GridNeighborhood2D();

    /**
     * @brief Destructor for the GridNeighborhood2D class.
     * 
     */
    ~GridNeighborhood2D();

    /**
     * @brief Initializes the GridNeighborhood2D class with a
     * predefined number of particles.
     * 
     * @param numParticles Number of particles in the system.
     */
    GridNeighborhood2D(const int numberOfpoints);

    /**
     * @brief Set the resolution of the grid.
     * 
     * @param width: Width of the grid.
     * @param height: Height of the grid.
     * @param kernelRadius: Kernel radius.
     */
    void setGridResolution(int width, int height, double kernelRadius) override;

    /**
	 * @brief Loop through all neighbor particles of the given particle,
	 * invoking a call to callback on each neighbor.
	 * 
	 * @param origin: Index of the particle that will have it's neighborhood
	 * looped through. 
	 * @param callback: Callback function to be invoked on each neighbor. 
	 */
    void forEachNearbyPoint(
		const int origin,
		const ForEachNearbyPointFunc& callback) const override;

    /**
	 * @brief Builds the neighorhood's iternal structure.
	 * 
	 * @param points: array of all points that will be part of the neighborhood.
	 */
	void build(const std::vector<Eigen::Vector2d>& points) override;

    /**
	 * @brief Get the Distances of a particle to it's neighbors.
	 * 
	 * @param index: index of the particle to get the distances of.
	 * @return std::vector<double> represeting the list of distances.
	 */
    std::vector<double> getDistances(int index) override;

private:
    /**
     * @brief Neighbors sorted according to particle index.
     * 
     */
    std::vector<Neighbor> _sortedNeighbors;

    /**
     * @brief Grid of neighbor pointers.
     * 
     */
    std::vector<Neighbor *> _grid;

    /**
     * @brief Indices of the particles in the grid.
     * 
     */
    std::vector<Eigen::Vector2i> _gridIndices;

    /**
     * @brief List containing the neighborhood of each particle.
     * 
     */
    std::vector<Neighborhood> _neighborhoods;

    /**
     * @brief Width of the grid.
     * 
     */
    int _width = 100;

    /**
     * @brief Height of the grid.
     * 
     */
    int _height = 100; 

    /**
     * @brief The cize of each grid cell.
     * 
     */
    double _cellSize = 1.0;

    /**
     * @brief Number of cells on the grid.
     * 
     * 
     */
    int _numCells = 100;
};

/**
 * @brief std::shared_ptr to the GridNeighborhood2D class.
 * 
 */
typedef std::shared_ptr<GridNeighborhood2D> GridNeighborhood2DPtr; 

#endif