# Compiler
CC := g++

INCLUDE := /usr/include ./
LINKING := /usr/lib

LIBLIST1 := GL GLEW
LIBLIST2 := glfw3

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
SHADERS_FRAGMENT_COMPONENTS := Utils.glsl Ray.glsl Interval.glsl Material.glsl HitRecord.glsl Scatter.glsl World.glsl Cube.glsl Sphere.glsl Camera.glsl
SHADERS_VF := shaders/vertex.glsl shaders/fragment.glsl shaders/compute.glsl
SFD_DIRECTORY := $(foreach fyle, $(SHADERS_FRAGMENT_COMPONENTS), shaders/Fragment\ Components/$(fyle))


application: new.cpp shaders/combined.glsl
	$(CC) $(CCFLAGS) -o $@ $< $(INCFLAG) $(LINFLAG) $(LIBFLAG1) $(LIBFLAG2)
	./$@ shaders/combined.glsl

prime-run: new.cpp shaders/combined.glsl
	$(CC) $(CCFLAGS) -o $@ $< $(INCFLAG) $(LINFLAG) $(LIBFLAG1) $(LIBFLAG2)
	./$@ shaders/combined.glsl

shaders/combined.glsl: concat.py $(SHADERS_VF) $(SFD_DIRECTORY)
	python3 $<
	rm shaders/combined_compute.glsl