# Smoothed Particle Hydrodynamics

This project implements a base SPH solver [1] and extends it to create a Viscoelastic SPH solver [2] that utilizes parallel processing with OpenMP.

The GIFs bellow show renders of the complete Viscoelastic SPH implementation:

<img src="./media/VSPHSpeed.gif" width="450">

Figure 1: Viscoelastic SPH implementation sped up with clideo.com for better visualization.

<br>

<img src="./media/VSPH.gif" width="450">

Figure 2: Viscoelastic SPH implementation running in real time.


This project also implements a way to save the results of a simulation in CSV files and to read them, respectivelly on CsvWriter.h and CsvReader.h.

## Dependencies

Currently, the code supports the linux environment, with the following dependencies:

 - g++ with C++20.
 - OpenMP 4.5.
 - OpenGL 3.1 with glut.

 ## Installation

There are many distributions of Linux, each with it's own download manager. In this example installation, we will stick with Ubuntu 20.04.

 - g++ with C++20:

```shell
    $ sudo apt install build-essential
```

 - OpenMP 4.5:

```shell
    $ sudo apt-get install libomp-dev
```

 - OpenGL 3.1 with glut:

```shell
    $ sudo apt-get install freeglut3-dev
```

## Usage

The goal of this project is to be a base that makes it possible to implement more solvers and save simulation data on CSV format.
Therefore, you can se examples of usage o tests/manual and tests/prepareCSVData.

To run those tests, you can use the following commands:

 - For tests/prepareCSVData:

```shell
    $ cd tests/prepareCSVData
    $ sh createCSVs.sh
```

 - For tests/manual, you can run the simulation for both SphSolver2D and VSphSolver2D:

For SphSolver2D:

```shell
    $ cd tests/manual
    $ sh runSphSolver2DRenderTest.sh
```
Or for VSphSolver2D:

```shell
    $ cd tests/manual
    $ sh runVSphSolver2DRenderTest.sh
```

You can also run the automated tests with:

```shell
    $ cd tests/automated
    $ sh solversTest.sh
```

## References

**[1]** MÜLLER, M. and CHARYPAR, D. and GROSS, M. - "Particle-Based Fluid Simulation for Interactive Applications" - Eurographics/SIGGRAPH Symposium on Computer Animation (2003). <br>
**[2]** CLAVET S. and BEAUDOIN, P. and POULIN, P. - "Particle-based viscoelastic fluid simulation" - Proceedings of the 2005 ACM SIGGRAPH/Eurographics symposium on Computer animationJuly 2005 Pages 219–228 <br>
**[3]** SOLENTHALER, B. and PAJAROLA, R. - "Predictive-corrective incompressible SPH" - SIGGRAPH '09: ACM SIGGRAPH 2009 papersJuly 2009 Article No.: 40 Pages 1–6. <br>
**[4]** BRIDSON, R. - "Fluid Simulation for Computer Graphics". <br>
**[5]** KIM, D. - "Fluid Engine Development". <br>
**[6]** SCHUERMANN, L. - "Concise SPH" - https://github.com/cerrno/mueller-sph <br>
**[7]** SCHUERMANN, L. - "Concise PCI-SPH" - https://github.com/cerrno/pcisph <br>