#include <cmath>
#include "../include/Vec4.hpp"

double vec4::length3() const{ return std::sqrt(el[0]*el[0] + el[1]*el[1] + el[2]*el[2]); }

double vec4::length3squared() const{ return (el[0]*el[0] + el[1]*el[1] + el[2]*el[2]); }

double vec4::euclidean_norm() const{ return std::sqrt(el[0]*el[0] + el[1]*el[1] + el[2]*el[2] + el[3]*el[3]); }

double & vec4::operator[](int index){ return el[index]; }

double dot3(const vec4 & v1, const vec4 & v2){
	return (v1.el[0]*v2.el[0] + v1.el[1]*v2.el[1] + v1.el[2]*v2.el[2]);
}

vec4 cross3(const vec4 & v1, const vec4 & v2){
	return vec4(
		v1.el[1]*v2.el[2] - v1.el[2]*v2.el[1],
		v1.el[2]*v2.el[0] - v1.el[0]*v2.el[2],
		v1.el[0]*v2.el[1] - v1.el[1]*v2.el[0],
		1.0
	);
}

vec4 operator* (const vec4 & v, double scalar){
	return vec4(v.el[0] * scalar, v.el[1] * scalar, v.el[2] * scalar, 1.0);
}

vec4 operator* (double scalar, const vec4 & v){
	return vec4(scalar * v.el[0], scalar * v.el[1], scalar * v.el[2], 1.0);
}

void vec4::operator*= (double scalar){
	el[0] *= scalar; el[1] *= scalar; el[2] *= scalar;
}

vec4 vec4::operator/  (double scalar) const{
	return vec4(el[0]/scalar, el[1]/scalar, el[2]/scalar, 1.0);
}

void vec4::operator/= (double scalar){
	el[0] /= scalar; el[1] /= scalar; el[2] /= scalar;
}

std::ostream & operator<<(std::ostream & os, const vec4 & v){
	os << "(" << v.el[0] << ", " << v.el[1] << ", " << v.el[2] << ", " << v.el[3] << ")";
	return os;
}
