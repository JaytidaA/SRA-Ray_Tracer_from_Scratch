# Compiler
CC := g++

# Linker Paths
INCLUDE := /usr/include /usr/local/include
LIBRARY := /usr/lib /usr/local/lib

# Linker files
# These are for the current project, they may change for future projects
libLINKS1 := GL GLEW
libLINKS2 := glfw3 X11

# Linker Flags
# "fyle" is used because "file" has another meaning in Makefiles
fgINCLLINKER := $(foreach path, $(INCLUDE), -I$(path)) \
            $(foreach path, $(LIBRARY), -L$(path))

libLINKER1 := $(foreach fyle, $(libLINKS1), -l$(fyle))
libLINKER2 := $(foreach fyle, $(libLINKS2), -l$(fyle))

# Compiler Flags
fgCOMPILER := -Wall -Wextra -O2

# The Target "Application"
classFILES1 := VertexBuffer.cpp IndexBuffer.cpp
classFILES2 := VertexArray.cpp
classFILES3 := VertexBufferLayout.cpp
classFILES4 := Shader.cpp
classOBJECTS1 := $(classFILES1:.cpp=.o)
classOBJECTS2 := $(classFILES2:.cpp=.o)
classOBJECTS3 := $(classFILES3:.cpp=.o)
classOBJECTS4 := $(classFILES4:.cpp=.o)

application: application.cpp Renderer.o $(classOBJECTS1) $(classOBJECTS2) $(classOBJECTS3) $(classOBJECTS4)
	$(CC) $(fgCOMPILER) $(fgINCLLINKER) -o $@ $^ $(libLINKER1) $(libLINKER2)

# Renderer Target
Renderer.o: Renderer.cpp Renderer.hpp
	$(CC) $(fgCOMPILER) $(fgINCLLINKER) -o $@ -c $< $(libLINKER1)

# Object Targets
$(classOBJECTS2): $(classFILES2) $(classFILES2:.cpp=.hpp) Renderer.o VertexBuffer.o $(classOBJECTS3)
	$(CC) $(fgCOMPILER) -o $@ -c $< Renderer.o VertexBuffer.o $(classOBJECTS3)

$(classOBJECTS3): $(classFILES3) $(classFILES3:.cpp=.hpp)
	$(CC) $(fgCOMPILER) $(fgINCLLINKER) -o $@ -c $< $(libLINKER1)

$(classOBJECTS4): $(classFILES4) $(classFILES4:.cpp=.hpp) Renderer.o
	$(CC) $(fgCOMPILER) $(fgINCLLINKER) -o $@ -c $< Renderer.o $(libLINKER1)

%.o: %.cpp %.hpp
	$(CC) $(fgCOMPILER) -o $@ -c $< Renderer.o

# PHONY Targets
.PHONY: clean clean-all

# Clean Target
clean:
	@ echo "Cleaning"
	@ rm -rf *.o

clean-all:
	@ make clean	
	rm application
