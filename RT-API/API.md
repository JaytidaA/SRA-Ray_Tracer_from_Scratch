This markdown file explains the API Usage for the different classes and methods for the Ray Tracing Application.

# Vec4.hpp

This file contains the `vec4` class which is widely used for positioning as well as for colours.

The class makes use of a `std::array` to hold the elements of the vector which are of type `double`. This class contains functions for accessing the elements as well as some basic arithmetic operations. The functions are stated below:

1. `x()`, `y()`, `z()`, `w()`: `const` functions which return elements by value. Use these as getters.
2. `operator[]`: Returns a reference to the element at the specified index. Use it as a setter.
3. `operator +(-)`: Overloaded functions which returns a `vec4` which contains the element-wise sums(differences) if another `vec4` has been passed to it. Returns a `vec4` where each element has been incremented(decremented) by the provided scalar.
4. `operator *(/)`: Returns a `vec4` scaled by the (reciprocal of the) specified scalar.
5. `operator`x`=`: Shorthand assignment implementations of all the arithmetic operations discussed above. (x := `+, -, *, /`)