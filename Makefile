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

prime-run: application.cpp
	$(CC) $(CCFLAGS) -o $@ $< $(INCFLAG) $(LINFLAG) $(LIBFLAG1) $(LIBFLAG2)
	prime-run ./$@
