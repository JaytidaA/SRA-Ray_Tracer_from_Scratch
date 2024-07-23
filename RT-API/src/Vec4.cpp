#include "../include/Vec4.hpp"
#include <cassert>

double & vec4::operator[](int i){
    assert(0 <= i <= 4);
    return my_Elem[i];
}

vec4 vec4::operator-(){
    return vec4(
        -my_Elem[0],
        -my_Elem[1],
        -my_Elem[2],
        -my_Elem[3]
    );
}

vec4 vec4::operator+(const vec4 & opd2){
    return vec4(
        my_Elem[0] + opd2.x(),
        my_Elem[1] + opd2.y(),
        my_Elem[2] + opd2.z(),
        my_Elem[3] + opd2.w()
    );
}

vec4 vec4::operator-(const vec4 & opd2){
    return vec4(
        my_Elem[0] - opd2.x(),
        my_Elem[1] - opd2.y(),
        my_Elem[2] - opd2.z(),
        my_Elem[3] - opd2.w()
    );
}

double dot3(const vec4 & v1, const vec4 & v2){
    return (
        v1.my_Elem[0] * v2.my_Elem[0] +
        v1.my_Elem[1] * v2.my_Elem[1] +
        v1.my_Elem[2] * v2.my_Elem[2]
    );
}

vec4 cross3(const vec4 & v1, const vec4 & v2){
    return vec4(
        v1.my_Elem[1] * v2.my_Elem[2] - v1.my_Elem[2] * v2.my_Elem[1],
        v1.my_Elem[2] * v2.my_Elem[0] - v1.my_Elem[0] * v2.my_Elem[2],
        v1.my_Elem[0] * v2.my_Elem[1] - v1.my_Elem[1] * v2.my_Elem[0],
        1.0
    );
}

void vec4::operator+=(const vec4 & opd2){
    my_Elem[0] += opd2.x();
    my_Elem[1] += opd2.y();
    my_Elem[2] += opd2.z();
    my_Elem[3] += opd2.w();
}

void vec4::operator-=(const vec4 & opd2){
    my_Elem[0] -= opd2.x();
    my_Elem[1] -= opd2.y();
    my_Elem[2] -= opd2.z();
    my_Elem[3] -= opd2.w();
}

vec4 vec4::operator+(double scalar){
    return vec4(
        my_Elem[0] + scalar,
        my_Elem[1] + scalar,
        my_Elem[2] + scalar,
        my_Elem[3] + scalar
    );
}

vec4 vec4::operator-(double scalar){
    return vec4(
        my_Elem[0] - scalar,
        my_Elem[1] - scalar,
        my_Elem[2] - scalar,
        my_Elem[3] - scalar
    );
}

vec4 vec4::operator*(double scalar){
    return vec4(
        my_Elem[0] * scalar,
        my_Elem[1] * scalar,
        my_Elem[2] * scalar,
        my_Elem[3] * scalar
    );
}

vec4 vec4::operator/(double scalar){
    return vec4(
        my_Elem[0] / scalar,
        my_Elem[1] / scalar,
        my_Elem[2] / scalar,
        my_Elem[3] / scalar
    );
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

void print3(std::ostream & os, const vec4 & vec){
    os << vec.my_Elem[0] << " " << vec.my_Elem[1] << " " << vec.my_Elem[2];
}

void print3colour(std::ostream & os, const vec4 & vec, int maxint){
    double multiplier = (double)maxint - 0.01;
    int carr[] = {
        int(multiplier * vec.my_Elem[0]),
        int(multiplier * vec.my_Elem[1]),
        int(multiplier * vec.my_Elem[2])
    };
    os << carr[0] << " " << carr[1] << " " << carr[2];
}