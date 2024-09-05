# Ray Tracer Renderer

It is a 3D renderer with ray tracing support, written in C++ and OpenGL from scratch.
Ray tracing is a common technique for generating photo-realistic digital imagery.

![cornell-sim](https://github.com/artemsuvorov/raytracer/assets/48320664/694799a0-22c9-42d5-97c0-11a0f23d31fb)
![showcase-2](https://github.com/user-attachments/assets/3fb2de5e-9345-4030-980a-5fefac655adc)



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
cd build && make && cd ..
```
Also, might need to install:
```sh 
sudo apt-get install libgl1-mesa-dev
sudo apt install libwayland-dev libxkbcommon-dev xorg-dev
```

You can check out other dependencies for Linux [here](https://www.glfw.org/docs/latest/compile_guide.html#compile_deps).

### Windows

```sh
cmake -S . -B build/ -G "MinGW Makefiles"
mingw32-make -C .\build\
```
