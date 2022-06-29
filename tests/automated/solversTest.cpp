/**
 * @file solversTest.cpp
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Implementation of the automated tests for the 2D Solvers.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#include "../../include/CsvReader.h"
#include "../../include/SphSolver2D.h"
#include "../../include/VSphSolver2D.h"

#include <iostream>
#include <eigen3/Eigen/Dense>

/**
 * @brief The tolerance for the tests.
 * 
 */
static const double ERROR_TOLERANCE = 1e-5;

/**
 * @brief Test function for SphSolver2D: Compare current solver to benchmark on CSV file.
 * 
 */
void sphSolver2DTest() {
    std::ifstream file("SphSolver2DData.csv");
    SphSolver2D solver(500);

    for(auto& row: CSVRange(file)) {
        solver.update();
        auto positions = solver.getPositions();

        for (int i = 0; i < positions.size(); i++) {
            Eigen::Vector2d position = positions[i];
            std::string expectedPositionStr = std::string(row[i]);
            Eigen::Vector2d expectedPosition = get2DVector(expectedPositionStr);

            if (!((position - expectedPosition).norm() < ERROR_TOLERANCE)) {
                std::cout << "SphSolver2D Test: FAILED!" << std::endl;
                return;
            }   
        }
    }

    std::cout << "SphSolver2D Test: PASSED!" << std::endl;
}

/**
 * @brief Test function for VSphSolver2D: Compare current solver to benchmark on CSV file.
 * 
 */
void vSphSolver2DTest() {
    std::ifstream file("VSphSolver2DData.csv");
    VSphSolver2D solver(50*50);

    for(auto& row: CSVRange(file)) {
        solver.update();
        auto positions = solver.getPositions();

        for (int i = 0; i < positions.size(); i++) {
            Eigen::Vector2d position = positions[i];
            std::string expectedPositionStr = std::string(row[i]);
            Eigen::Vector2d expectedPosition = get2DVector(expectedPositionStr);

            if (!((position - expectedPosition).norm() < ERROR_TOLERANCE)) {
                std::cout << "VSphSolver2D Test: FAILED!" << std::endl;
                return;
            }   
        }
    }

    std::cout << "VSphSolver2D Test: PASSED!" << std::endl;
}

int main(int argc, char **argv) {
    sphSolver2DTest();
    vSphSolver2DTest();
    return 0;
}