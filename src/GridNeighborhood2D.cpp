/**
 * @file GridNeighborhood2D.cpp
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Implementation of the Grid Neighborhood for 2D particle systems.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#include "../include/GridNeighborhood2D.h"
#include "../include/Constants.h"

GridNeighborhood2D::GridNeighborhood2D() : ParticleNeighborhood2D() {
    _sortedNeighbors = {};
	_neighborhoods = {};

	for (int i = 0; i < MAX_PARTICLES2D; i++) {
		_sortedNeighbors.push_back(Neighbor(i));
		_neighborhoods.push_back(Neighborhood());
	}	
}   

GridNeighborhood2D::GridNeighborhood2D(const int numberOfpoints) : ParticleNeighborhood2D() {
    _sortedNeighbors = {};
	_neighborhoods = {};

	for (int i = 0; i < numberOfpoints; i++) {
		_sortedNeighbors.push_back(Neighbor(i));
		_neighborhoods.push_back(Neighborhood());
	}	
}

GridNeighborhood2D::~GridNeighborhood2D() { }

void GridNeighborhood2D::setGridResolution(int width, int height, double kernelRadius) {
    _cellSize = kernelRadius;
    _width = (int) width / _cellSize;
    _height = (int) height / _cellSize;
    _numCells = _width * _height;
    _grid = std::vector<Neighbor *>(_numCells, nullptr);
    _gridIndices = std::vector<Eigen::Vector2i>(MAX_PARTICLES2D, Eigen::Vector2i(0, 0));
}

void GridNeighborhood2D::forEachNearbyPoint( const int origin,
    const ForEachNearbyPointFunc& callback) const {

	#ifndef TEST
		#pragma omp parallel for
	#endif
    for (int i = 0; i < _neighborhoods[origin].numNeighbors; i++) {
        callback(_neighborhoods[origin].neighbors[i]->index, _neighborhoods[origin].distances[i]);
    }
}

void GridNeighborhood2D::build(const std::vector<Eigen::Vector2d>& points) {
	#ifndef TEST
		#pragma omp parallel for
	#endif
	for (auto &elem : _grid)
		elem = nullptr;
	
	#ifndef TEST
		#pragma omp parallel for
	#endif
	for (int i = 0; i < points.size(); i++) {
		auto p = points[i];
        auto& n = _sortedNeighbors[i];
		int xind = p(0) / _cellSize;
		int yind = p(1) / _cellSize;
		xind = std::max(1, std::min(_width - 2, xind));
		yind = std::max(1, std::min(_height - 2, yind));
		n.next = _grid[xind + yind * _width];
		_grid[xind + yind * _width] = &n;
		_gridIndices[i] = Eigen::Vector2i(xind, yind);
	}

	#ifndef TEST
		#pragma omp parallel for
	#endif
    for (int i = 0; i < points.size(); i++)
	{
		auto &pi = points[i];

		Eigen::Vector2i gridIndex = Eigen::Vector2i(_gridIndices[i](0), _gridIndices[i](1) * _width);
		_neighborhoods[i].numNeighbors = 0;

		double dens = 0.0f;
		double dens_proj = 0.0f;
		for (int ii = gridIndex(0) - 1; ii <= gridIndex(0) + 1; ii++) {
			for (int jj = gridIndex(1) - _width; jj <= gridIndex(1) + _width; jj += _width) {
				for (Neighbor *pgrid = _grid[ii + jj]; pgrid != NULL; pgrid = pgrid->next)
				{
					const Eigen::Vector2d &pj = points[pgrid->index];
					Eigen::Vector2d dx = pj - pi;
					double r2 = dx.squaredNorm();
					if (r2 < EPS || r2 > _cellSize * _cellSize)
						continue;

                    double r = sqrt(r2);
					if (_neighborhoods[i].numNeighbors < Neighborhood::MAX_NEIGHBORS)
					{
						_neighborhoods[i].neighbors[_neighborhoods[i].numNeighbors] = pgrid;
						_neighborhoods[i].distances[_neighborhoods[i].numNeighbors] = r;
						++_neighborhoods[i].numNeighbors;
					}
				}
            }
        }
	}
}

std::vector<double> GridNeighborhood2D::getDistances(int index) {
    return _neighborhoods[index].distances;
}