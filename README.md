# Ray Tracer Renderer

It is a 3D renderer with ray tracing support, written in C++ and OpenGL from scratch.
Ray tracing is a common technique for generating photo-realistic digital imagery.


## Quick Start

Make sure the project repository has been cloned with the `--recursive-submodules` flag to additionally clone all the included submodules.

```
git clone --recurse-submodules -j8 https://github.com/artemsuvorov/raytracer.git
```

Otherwise, for already cloned repository, submodules can be cloned via:

```
git submodule update --init --recursive
```

Now, the project can be built and compiled into an executable file using `CMake` from the project directiory `raytracer`. 

### Linux (Ubuntu)

```sh
cmake -S . -B build
make -C . build
```
Also, might need to install:
```sh 
sudo apt-get install libgl1-mesa-dev
```

### Windows

```sh
cmake -S . -B build/ -G "MinGW Makefiles"
mingw32-make -C .\build\
```