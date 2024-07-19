This markdown file explains the API Usage for the different classes and methods for the Ray Tracing Application.

# Vec4.hpp

This file contains the `vec4` class which is widely used for positioning as well as for colours.

The class makes use of a `std::array` to hold the elements of the vector which are of type `double`. This class contains functions for accessing the elements as well as some basic arithmetic operations. The functions are stated below:

1. `x()`, `y()`, `z()`, `w()`: `const` functions which return elements by value. Use these as getters.
2. `operator[]`: Returns a reference to the element at the specified index. Use it as a setter.
3. `operator -`: This is the unary minus operator used to reverse the direction of the vector.
4. `operator +(-)`: Overloaded functions which returns a `vec4` which contains the element-wise sums(differences) if another `vec4` has been passed to it. Returns a `vec4` where each element has been incremented(decremented) by the provided scalar.
5. `operator *(/)`: Returns a `vec4` scaled by the (reciprocal of the) specified scalar.
6. `operator`x`=`: Shorthand assignment implementations of all the arithmetic operations discussed above. (x := `+, -, *, /`)

# sMatrix4.hpp

This file contains the `smatrix4` class which is used for applying Linear Transformations on the `vec4` class.

The class makes use of a `std::array` of 4 `vec4` objects. Each such vector represents a column of the matrix. This also means that each vector used by the API represents a column vector. The functions for this class are the basic element access and matrix-matrix muliplication as well as the matrix-vector multiplication. The addition and subtraction operations are not implemented.

1. `c0()`, `c1()`, `c2()`, `c3()`: `const` functions which return the column vectors by values. Use these as getters.
2. `operator[]`: Returns a reference to the `vec4` vector at the specified index. Use this as a setter.
3. `operator *`: Overloaded function which either returns a `vec4` or a `smatrix4` depending on the input. The returned result is the product of the matrix-matrix multiplication of the two operands(remember a vector is just a column matrix).