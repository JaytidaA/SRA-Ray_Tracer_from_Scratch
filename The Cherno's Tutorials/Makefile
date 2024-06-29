# Get the Command Line Argument
BASESRC := $(basename $(notdir $(firstword $(MAKECMDGOALS))))


# Compiler
CC := g++

# Linker Paths
INCLUDE := /usr/include /usr/local/include
LIBRARY := /usr/lib /usr/local/lib

# Linker files
# These are for the current project, they may change for future projects
libLINKS := GL GLEW glfw3 X11

# Linker Flags
# "fyle" is used because "file" has another meaning in Makefiles
fgLINKER := $(foreach path, $(INCLUDE), -I$(path)) \
            $(foreach path, $(LIBRARY), -L$(path))

libLINKER := $(foreach fyle, $(libLINKS), -l$(fyle))

# Compiler Flags
fgCOMPILER := -Wall

# The Default Target, accepts a .cpp file
.DEFAULT_GOAL := $(BASESRC)

$(BASESRC): $(BASESRC).cpp
	$(CC) $(fgCOMPILER) $(fgLINKER) -o $@ $< $(libLINKER)

