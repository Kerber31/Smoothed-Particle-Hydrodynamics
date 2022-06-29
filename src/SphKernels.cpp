/**
 * @file SphKernels.h
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Implementation of the kernels for SPH simulators.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#include "../include/SphKernels.h"
#include "../include/Constants.h"

SphPoly6Kernel::SphPoly6Kernel(double kernelRadius_) {
    kernelRadius = kernelRadius_;
}

double SphPoly6Kernel::operator()(double distanceSquaredDifference) const {
    return (4.f / (M_PI * pow(kernelRadius, 8.0))) * pow(distanceSquaredDifference, 3.0);
}

SphSpikyKernel::SphSpikyKernel(double kernelRadius_) {
    kernelRadius = kernelRadius_;
}   

double SphSpikyKernel::gradientAt(double distanceSquaredDifference) const {
    return (-10.0 / (M_PI * pow(kernelRadius, 5.0))) * pow(distanceSquaredDifference, 3.0);
}   

SphViscosityKernel::SphViscosityKernel(double kernelRadius_) {
    kernelRadius = kernelRadius_;
}

double SphViscosityKernel::laplacianAt(double distanceSquaredDifference) const {
    return (40.0 / (M_PI * pow(kernelRadius, 5.0))) * distanceSquaredDifference;
}