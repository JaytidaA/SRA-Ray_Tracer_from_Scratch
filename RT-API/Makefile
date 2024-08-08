# Compiler and Compiler Flags
CC := g++
CCFLAGS := -Wall -Wextra -Wno-unused-parameter

# Include Files
HITINCLUDE := Hittable.hpp Sphere.hpp HittableList.hpp
INCLUDE := SussyUtility.hpp Vec4.hpp Ray.hpp Interval.hpp

# Include Paths
pathHITINCLUDE := $(foreach fyle, $(HITINCLUDE), include/$(fyle))
pathINCLUDE := $(foreach fyle, $(INCLUDE), include/$(fyle))

# Main File
main := main.cpp

# Targets
bin/Vec4.o: src/Vec4.cpp include/Vec4.hpp
	@ $(CC) $(CCFLAGS) -o $@ -c $<

output: bin/Vec4.o $(pathINCLUDE) $(pathHITINCLUDE)
	@ $(CC) $(CCFLAGS) -o $@ $(main) $<
