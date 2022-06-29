/**
 * @file prepareCSVs.cpp
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Implementation of the functions that generate benchmark CSV files for solver automated tests.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#include "../../include/SphSolver2D.h"
#include "../../include/VSphSolver2D.h"
#include <iostream>

/**
 * @brief The number of iterations for the tests.
 * 
 */
static const int NUMBER_OF_ITERATIONS = 500;

/**
 * @brief Creates a CSV file with the benchmark data for SphSolver2D.
 * 
 */
void createSphSolver2DCsvData() {
    SphSolver2D solver(500, "../automated/SphSolver2DData.csv");

    std::cout << "Creating CSV data for SphSolver2D..." << std::endl;

    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        solver.update();
    }

    std::cout << "SphSolver2DData.csv created." << std::endl;
}

/**
 * @brief Creates a CSV file with the benchmark data for VSphSolver2D.
 * 
 */
void createVSphSolver2DCsvData() {
    VSphSolver2D solver(50*50, "../automated/VSphSolver2DData.csv");

    std::cout << "Creating CSV data for VSphSolver2D..." << std::endl;

    for (int i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        solver.update();
    }

    std::cout << "VSphSolver2DData.csv created." << std::endl;
}

int main(int argc, char **argv) {
    createSphSolver2DCsvData();
    createVSphSolver2DCsvData();
    
    return 0;
}