/**
 * @file SphSolver2DRenderTest.cpp
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Implementation of the manual test for the SphSolver2D.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#include "../../include/SphSolver2D.h"
#include "../../include/GlutRenderer2D.h"

int main(int argc, char **argv) {
	setSolver(std::make_shared<SphSolver2D>(500));
	loop(argc, argv);

	return 0;
}