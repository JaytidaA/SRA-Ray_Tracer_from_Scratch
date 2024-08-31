# Compiler
CC := g++

INCLUDE := ./LIBRARIES/include ./
LINKING := ./LIBRARIES/bin/GLEW

LIBLIST1 := GL GLEW
LIBLIST2 := glfw

WINDOWING_SYSTEM :=$(shell if [ ! -z "$$WAYLAND_DISPLAY" ]; then echo "wayland"; else echo "x11"; fi)
ifeq ($(WINDOWING_SYSTEM),wayland)
	LIBLIST2 += wayland-client
	LIBLIST2 += wayland-egl
	LIBLIST2 += wayland-cursor
else
	LIBLIST2 += X11
endif	

# Compiler flags
CCFLAGS := -Wall -Wextra -O2

# Include flags
INCFLAG := $(foreach path, $(INCLUDE), -I$(path))
LINFLAG := $(foreach path, $(LINKING), -L$(path))

LIBFLAG1 := $(foreach fyle, $(LIBLIST1), -l$(fyle))
LIBFLAG2 := $(foreach fyle, $(LIBLIST2), -l$(fyle))

# Shader Parts
SHADERS_COMPUTE_COMPONENTS := Utils.glsl Ray.glsl Interval.glsl Material.glsl HitRecord.glsl Scatter.glsl Sphere.glsl Cylinder.glsl Cube.glsl World.glsl
SHADERS_VFC := Shaders/vertex.glsl Shaders/fragment.glsl Shaders/compute.glsl
SCD_DIRECTORY := $(foreach fyle, $(SHADERS_COMPUTE_COMPONENTS), Shaders/Compute\ Components/$(fyle))


application: application.cpp Shaders/combined.glsl
	$(CC) $(CCFLAGS) -o $@ $< $(INCFLAG) $(LINFLAG) $(LIBFLAG1) $(LIBFLAG2)
	./$@ Shaders/combined.glsl

prime-run: application.cpp Shaders/combined.glsl
	$(CC) $(CCFLAGS) -o $@ $< $(INCFLAG) $(LINFLAG) $(LIBFLAG1) $(LIBFLAG2)
	prime-run ./$@ Shaders/combined.glsl

Shaders/combined.glsl: concat_shaders.py $(SHADERS_VFC) $(SCD_DIRECTORY)
	python3 $<
	rm Shaders/combined_compute.glsl
