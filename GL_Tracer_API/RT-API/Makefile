# Compiler
CC := g++

INCLUDE := /usr/include
LINKING := /usr/lib

LIBLIST1 := GL GLEW
LIBLIST2 := glfw3 X11

# Compiler flags
CCFLAGS := -Wall -Wextra -O3

# Include flags
INCFLAG := $(foreach path, $(INCLUDE), -I$(path))
LINFLAG := $(foreach path, $(LINKING), -L$(path))

LIBFLAG1 := $(foreach fyle, $(LIBLIST1), -l$(fyle))
LIBFLAG2 := $(foreach fyle, $(LIBLIST2), -l$(fyle))
