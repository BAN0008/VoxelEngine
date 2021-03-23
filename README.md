# VoxelEngine
Engine for voxel games\
I don't really know where this project will go yet\
**Only linux is supported for now**\
It should be fairly simple to port to other operating systems though

## Build requirements
- meson
- A C++ compiler supporting C++17
- glfw 3.x headers and shared library
- glm 9.8 headers (older may work)

## Runtime requirements
- OpenGL 4.4 or higher
- ARB_direct_state_access or OpenGL 4.5
- glfw 3.x shared library

## Building
```
meson build
cd build
ninja
```
