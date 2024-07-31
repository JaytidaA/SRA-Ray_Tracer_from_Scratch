#include "../include/SqMatrix4.hpp"
#include <cassert>

vec4 & smatrix4::operator[](int i){
    assert((0 <= i) && (i <= 4));
    return my_Elem[i];
}

vec4 smatrix4::operator*(const vec4 & opd2){
    return (
        my_Elem[0] * opd2.x() +
        my_Elem[1] * opd2.y() + 
        my_Elem[2] * opd2.z() + 
        my_Elem[3] * opd2.w()
    );
}

smatrix4 smatrix4::operator*(const smatrix4 & opd2){
    vec4 col0 = *(this) * opd2.c0();
    vec4 col1 = *(this) * opd2.c1();
    vec4 col2 = *(this) * opd2.c2();
    vec4 col3 = *(this) * opd2.c3();

    smatrix4 res_Mat(col0, col1, col2, col3);
    return res_Mat;
}