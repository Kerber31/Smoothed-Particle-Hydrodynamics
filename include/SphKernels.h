/**
 * @file SphKernels.h
 * @author Matheus Kerber Veturelli (matheuskveturelli@gmail.com)
 * @brief Header of the kernels for SPH simulators.
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright MIT License 2022
 * 
 */

#ifndef SPHKERNELS_H
#define SPHKERNELS_H

/**
 * @brief Struct representig the Poly6 SPH kernel.
 * 
 */
struct SphPoly6Kernel {

    /**
     * @brief Construct a new SphPoly6Kernel object.
     * 
     * @param kernelRadius: The radius of the kernel. 
     */
    SphPoly6Kernel(double kernelRadius);

    /**
     * @brief Kernel radius of the kernel.
     * 
     */
    double kernelRadius;

    /**
     * @brief Compute the kernel value for the given distance squared difference.
     * 
     * @param distanceSquaredDifference: difference between two squared distances.
     * @return double representing the kernel value.
     */
    double operator()(double distanceSquaredDifference) const;
};

/**
 * @brief Struct representig the Spiky SPH kernel.
 * 
 */
struct SphSpikyKernel {
    /**
     * @brief Construct a new Sph Spiky Kernel object
     * 
     * @param kernelRadius: The radius of the kernel. 
     */
    SphSpikyKernel(double kernelRadius);

    /**
     * @brief Kernel radius of the kernel.
     * 
     */
    double kernelRadius;

    /**
     * @brief Compute the gradient of the kernel for the given distance squared difference.
     * 
     * @param distanceSquaredDifference: difference between two squared distances.
     * @return double representing the kernel value.
     */
    double gradientAt(double distanceSquaredDifference) const;
};

/**
 * @brief Struct representig the Viscosity SPH kernel.
 * 
 */
struct SphViscosityKernel {
    /**
     * @brief Construct a new Sph Viscosity Kernel object
     * 
     * @param kernelRadius: The radius of the kernel.
     */
    SphViscosityKernel(double kernelRadius);

    /**
     * @brief Kernel radius of the kernel.
     * 
     */
    double kernelRadius;

    /**
     * @brief Compute the laplacian of the kernel for the given distance squared difference.
     * 
     * @param distanceSquaredDifference: difference between two squared distances.
     * @return double representing the kernel value.
     */
    double laplacianAt(double distanceSquaredDifference) const;
};

#endif