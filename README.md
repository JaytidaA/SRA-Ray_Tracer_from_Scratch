# dev-Aaditya
This branch contains the code of the development release of the Ray-Tracer from Scratch Project for Eklavya 2024.

## Directories
### `GL\_Tracer\_API`
This directory contains the header files containing some helpful functions for the RayTracer.

### `Shaders`
This directory contains the different Shaders to be loaded in for the final application.

### `./`
The main directory itself contains the following files:
1. `application.cpp`: The main C++ file and the entry point of the program
2. `application`: The executable binary
3. `concat_shaders.py`: This file is used to concatenate the different glsl files present in `Shaders` into a larger combined Shader file. This is done because I like modularisation of my code components.
4. `Makefile`: Contains the build directions.
5. `README.md`: The README for this branch containing a brief overview of te files of this branch.

(There also exists a hidden directory `RT-API`, currently there is no use for this.)

## Directions for Building
After making the required changes to the `application.cpp` file or the shaders, you can simply execute the Makefile and the application will open.
```bash
make
```

If you want to reopen the application after the build once again you have to use the command:
```bash
./application Shaders/combined.glsl
```
if you do not want to build the project again.
