#include <eklVector.hpp>
#include <cmath>

namespace ekl{

vector operator + (const vector & v1, const vector & v2){
	return vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

vector operator - (const vector & v1, const vector & v2){
    return vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

vector operator * (const float k, const vector & v){
    return vector(k * v.x, k * v.y, k * v.z, k * v.w);
}

vector operator * (const vector & v, const float k){
	return vector(v.x * k, v.y * k, v.z * k, v.w * k);
}

vector operator / (const vector & v, const float k){
	return vector(v.x / k, v.y / k, v.z / k, v.w / k);
}

float vector::e_norm() const{
	return std::sqrt((x*x) + (y*y) + (z*z) + (w*w));
}

float vector::e_norm3() const{
	return std::sqrt((x*x)+(y*y)+(z*z));
}

float vector::e_norm3squared() const{
    return (x*x)+(y*y)+(z*z);
}

const float * vector::data() const{
	return &x;
}

};
