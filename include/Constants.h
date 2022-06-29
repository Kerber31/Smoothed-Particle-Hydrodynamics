/**
 * @file Constants.h
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Global constants for the solvers.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>
#include <eigen3/Eigen/Dense>

/**
 * @brief Gravity in 2D.
 * 
 */
const static Eigen::Vector2d G2D(0.0, -9.8);

/**
 * @brief Rest density of the system.
 * 
 */
const static double REST_DENSITY = 300.0;

/**
 * @brief Elastic rest density of the system.
 * 
 */
const static double ELASTIC_REST_DENSITY = 45.0;

/**
 * @brief Constat for the equation of state.
 * 
 */
const static double GAS_CONSTANT = 2000.0;

/**
 * @brief Maximum number of particles in the system.
 * 
 */
const static int MAX_PARTICLES2D = 75*75;

/**
 * @brief Mass of a particle.
 * 
 */
const static double PARTICLE_MASS = 1.0f;

/**
 * @brief Error tolerance
 * 
 */
const static double EPS = 0.00001f;

/**
 * @brief Error tolerance squared.
 * 
 */
const static double EPS2 = EPS * EPS;

#endif