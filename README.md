# Smoothed Particle Hydrodynamics

This project implements a base SPH solver [1] and extends it to create a Viscoelastic SPH solver [2] that utilizes parallel processing with OpenMP.

The GIF bellow shows a render of the complete Viscoelastic SPH implementation runnig in real time:

![](/media/VSPH.gif)

This project also implements a way to save the results of a simulation in CSV files and to read them.

## References

[1] **MÜLLER, M. and CHARYPAR, D. and GROSS, M.** - "Particle-Based Fluid Simulation for Interactive Applications" - Eurographics/SIGGRAPH Symposium on Computer Animation (2003). <br>
[2] **CLAVET S. and BEAUDOIN, P. and POULIN, P.** - "Particle-based viscoelastic fluid simulation" - Proceedings of the 2005 ACM SIGGRAPH/Eurographics symposium on Computer animationJuly 2005 Pages 219–228 <br>
[3] **SOLENTHALER, B. and PAJAROLA, R.** - "Predictive-corrective incompressible SPH" - SIGGRAPH '09: ACM SIGGRAPH 2009 papersJuly 2009 Article No.: 40Pages 1–6. <br>
[4] **BRIDSON, R.** - "Fluid Simulation for Computer Graphics". <br>
[5] **KIM, D.** - "Fluid Engine Development". <br>
[6] **SCHUERMANN, L.** - "Concise SPH" - https://github.com/cerrno/mueller-sph <br>
[7] **SCHUERMANN, L.** - "Concise PCI-SPH" - https://github.com/cerrno/pcisph <br>