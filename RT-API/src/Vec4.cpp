#include "../include/Vec4.hpp"
#include <cassert>

double & vec4::operator[](int i){
    assert(0 <= i <= 4);
    return my_Elem[i];
}

vec4 vec4::operator-(){
    vec4 res_Vec(
        -my_Elem[0],
        -my_Elem[1],
        -my_Elem[2],
        -my_Elem[3]
    );
    return res_Vec;
}

vec4 vec4::operator+(vec4 opd2){
    vec4 res_Vec(
        my_Elem[0] + opd2.x(),
        my_Elem[1] + opd2.y(),
        my_Elem[2] + opd2.z(),
        my_Elem[3] + opd2.w()
    );
    return res_Vec;
}

vec4 vec4::operator-(vec4 opd2){
    vec4 res_Vec(
        my_Elem[0] - opd2.x(),
        my_Elem[1] - opd2.y(),
        my_Elem[2] - opd2.z(),
        my_Elem[3] - opd2.w()
    );
    return res_Vec;
}

void vec4::operator+=(vec4 opd2){
    my_Elem[0] += opd2.x();
    my_Elem[1] += opd2.y();
    my_Elem[2] += opd2.z();
    my_Elem[3] += opd2.w();
}

void vec4::operator-=(vec4 opd2){
    my_Elem[0] -= opd2.x();
    my_Elem[1] -= opd2.y();
    my_Elem[2] -= opd2.z();
    my_Elem[3] -= opd2.w();
}

vec4 vec4::operator+(double scalar){
    vec4 res_Vec(
        my_Elem[0] + scalar,
        my_Elem[1] + scalar,
        my_Elem[2] + scalar,
        my_Elem[3] + scalar
    );
    return res_Vec;
}

vec4 vec4::operator-(double scalar){
    vec4 res_Vec(
        my_Elem[0] - scalar,
        my_Elem[1] - scalar,
        my_Elem[2] - scalar,
        my_Elem[3] - scalar
    );
    return res_Vec;
}

vec4 vec4::operator*(double scalar){
    vec4 res_Vec(
        my_Elem[0] * scalar,
        my_Elem[1] * scalar,
        my_Elem[2] * scalar,
        my_Elem[3] * scalar
    );
    return res_Vec;
}

vec4 vec4::operator/(double scalar){
    vec4 res_Vec(
        my_Elem[0] / scalar,
        my_Elem[1] / scalar,
        my_Elem[2] / scalar,
        my_Elem[3] / scalar
    );
    return res_Vec;
}

void vec4::operator+= (double scalar){
    my_Elem[0] += scalar;
    my_Elem[1] += scalar;
    my_Elem[2] += scalar;
    my_Elem[3] += scalar;
}

void vec4::operator-= (double scalar){
    my_Elem[0] -= scalar;
    my_Elem[1] -= scalar;
    my_Elem[2] -= scalar;
    my_Elem[3] -= scalar;
}

void vec4::operator*= (double scalar){
    my_Elem[0] *= scalar;
    my_Elem[1] *= scalar;
    my_Elem[2] *= scalar;
    my_Elem[3] *= scalar;
}

void vec4::operator/= (double scalar){
    my_Elem[0] /= scalar;
    my_Elem[1] /= scalar;
    my_Elem[2] /= scalar;
    my_Elem[3] /= scalar;
}

std::ostream& operator<<(std::ostream & out_Stream, const vec4 & vec){
    out_Stream << vec.x() << " " << vec.y() << " " << vec.z();
    return out_Stream;
}