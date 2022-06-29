/**
 * @file ParticleNeighborhood2D.h
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Header of the base particle neighborhood for 2D particle systems.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#ifndef PARTICLENEIGHBORHOOD2D_H
#define PARTICLENEIGHBORHOOD2D_H

#include <vector>
#include <functional>
#include <eigen3/Eigen/Dense>
#include <memory>

/**
 * @brief Class that implements the base particle neighborhood for 2D particle systems.
 * 
 */
class ParticleNeighborhood2D
{
public:

	/**
	 * @brief Default constructor for ParticleNeighborhood2D.
	 * 
	 */
	ParticleNeighborhood2D();

	/**
	 * @brief Destructor for ParticleNeighborhood2D.
	 * 
	 */
	virtual ~ParticleNeighborhood2D();

public:

	/**
	 * @brief typedef to efine a callback function to be called 
	 * by the method forEachNearyPoint.
	 * 
	 */
	typedef std::function<void(size_t, const double)>
		ForEachNearbyPointFunc;

	/**
	 * @brief Loop through all neighbor particles of the given particle,
	 * invoking a call to callback on each neighbor.
	 * 
	 * @param origin: Index of the particle that will have it's neighborhood
	 * looped through. 
	 * @param callback: Callback function to be invoked on each neighbor. 
	 */
	virtual void forEachNearbyPoint(
		const int origin,
		const ForEachNearbyPointFunc& callback) const = 0;

	/**
	 * @brief Builds the neighorhood's iternal structure.
	 * 
	 * @param points: array of all points that will be part of the neighborhood.
	 */
	virtual void build(const std::vector<Eigen::Vector2d>& points) = 0;

	/**
	 * @brief Get the Distances of a particle to it's neighbors.
	 * 
	 * @param index: index of the particle to get the distances of.
	 * @return std::vector<double> represeting the list of distances.
	 */
	virtual std::vector<double> getDistances(int index) = 0;

	/**
	 * @brief Set the resolution of the grid.
	 * 
	 * @param width: the width resolution.
	 * @param height: the height resolution.
	 * @param kernelRadius: the kernel radius.
	 */
	virtual void setGridResolution(int width, int height, double kernelRadius) = 0;
};

/**
 * @brief std::shared_ptr to ParticleNeighborhood2D.
 * 
 */
typedef std::shared_ptr<ParticleNeighborhood2D> ParticleNeighborhood2DPtr;

#endif // PARTICLENEIGHBORHOOD2D_H