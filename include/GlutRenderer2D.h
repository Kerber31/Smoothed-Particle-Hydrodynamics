/**
 * @file GlutRenderer2D.h
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Header of the Glut Renderer for 2D particle systems.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#ifndef GLUTRENDERER2D_H
#define GLUTRENDERER2D_H

#include <GL/glut.h>
#include <memory>
#include "SphSolver2D.h"

/**
 * @brief The SPH solver pointer for 2D particle systems to be rendered.
 * 
 */
static SphSolver2DPtr solver;

/**
 * @brief The main loop of the animation to be rendered.
 * 
 * @param argc: The number of arguments.
 * @param argv: The arguments.
 */
void loop(int argc, char **argv);

/**
 * @brief Render a frame.
 * 
 */
void render();

/**
 * @brief Update the animation.
 * 
 */
void update();

/**
 * @brief Initialize the OpenGL context.
 * 
 */
void initGL();

/**
 * @brief Set the Solver object
 * 
 * @param solver_: Solver pointer to a SPH solver.
 */
void setSolver(SphSolver2DPtr solver_);

#endif