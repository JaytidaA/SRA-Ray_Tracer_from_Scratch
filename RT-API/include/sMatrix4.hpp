#ifndef SMATRIX4_HPP
#define SMATRIX4_HPP

#include "Vec4.hpp"
#include <array>

class smatrix4{
    private:
    std::array<vec4, 4> my_Elem;

    public:
    // Null Matrix
    smatrix4(): my_Elem({vec4(0.0), vec4(0.0), vec4(0.0), vec4(0.0)}){}

    // Diagonal Matrix
    smatrix4(double value, bool homogeneous = false){
        my_Elem[0] = vec4(value, 0, 0, 0);
        my_Elem[1] = vec4(0, value, 0, 0);
        my_Elem[2] = vec4(0, 0, value, 0);
        my_Elem[3] = vec4(0, 0, 0, (homogeneous)?1.0:value);
    }

    // Matrix made from 4 vectors
    smatrix(std::array<vec4, 4> entries): my_Elem(entries){}
    smatrix(vec4 en0, vec4 en1, vec4 en2, vec4 en3): my_Elem({en0, en1, en2, en3}){}

    public:
    // Vector Access
    vec4 c0() const{ return my_Elem[0]; }
    vec4 c1() const{ return my_Elem[1]; }
    vec4 c2() const{ return my_Elem[2]; }
    vec4 c3() const{ return my_Elem[3]; }

    vec4 & operator[](int);

    public:
    // Matrix Multiplication
    vec4 operator*(vec4);
    smatrix4 operator*(smatrix4);
};

#endif //SMATRIX4_HPP