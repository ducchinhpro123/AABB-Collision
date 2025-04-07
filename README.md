# AABBCollision

A C++ project for AABB (Axis-Aligned Bounding Box) collision detection using SFML.

## Requirements

- Meson build system
- Ninja build backend
- C++ compiler (GCC, Clang, etc.)
- SFML library (libsfml-dev package on Debian/Ubuntu)

## Building

```bash
# Configure the build
meson setup builddir

# Compile the project
meson compile -C builddir

# Run the executable
./builddir/aabb_collision
```

## Development

To reconfigure with different options:

```bash
meson configure builddir -Dbuildtype=debug
``` 