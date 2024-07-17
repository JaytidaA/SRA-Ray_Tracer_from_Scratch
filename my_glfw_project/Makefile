# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Iglad/include -I/usr/local/include -I/usr/include/GL -I/usr/include/glm

# Linker flags
LDFLAGS = -L/usr/local/lib -L/usr/lib -lglfw3 -lGLEW -lGL -ldl

# Source files
SRCS = pyramid.cpp glad/src/glad.c

# Output binary
TARGET = openGLProject

# Default rule
all: $(TARGET)

# Rule to link object files to create the binary
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Clean rule
clean:
	rm -f $(TARGET) *.o
