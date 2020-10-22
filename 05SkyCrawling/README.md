# SkyCrawling

Crawling in an unknown solar system with limited ability to move and zoom.

## Tasks

Build a solar system with OpenGL.

* One sun, 2+ planets, 1+ satellite
* Planets orbit around the sun
* Satellites orbit around its planet
* Trajectories are *not co-planar*
*  Navigation in the system (3D viewing)
`E.g., W+S+A+D -> walk, mouse-move -> change viewdir`

## Prerequsites

* CMake
* VisualStudio | MinGW
* OpenGL

Make sure you have cmake and Visual Studio properly installed on your computer.

## Installation

Assume you are now under the directory of the README file. 

```bash
mkdir build && cd build
cmake .. -G <"Visual Studio 16 2019" | "MinGW Makefiles">
```

CMake will then generate a solution file if all goes well.
Open the solution in Visual Studio and start building.
