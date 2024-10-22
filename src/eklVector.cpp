#include <eklVector>
#include <cmath>

namespace ekl{

vector vector::operator + (const vector & v1, const vector & v2){
	return vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

vector vector::operator - (const vector & v1, const vector & v2){
    return vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

vector vector::operator * (const float k, const vector & v){
    return vector(k * v.x, k * v.y, k * v.z, k * v.w);
}

vector vector::operator * (const vector & v, const float){
	return vector(v.x * k, v.y * k, v.z * k, v.w * k);
}

vector vector::operator / (const vector & v, const float){
	return vector(v.x / k, v.y / k, v.z / k, v.w / k);
}

float norm(){
	return std::sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z) + (v.w*v.w));
}

float norm3(){
	return std::sqrt((v.x*v.x)+(v.y*v.y)+(v.z*v.z));
}

float norm3squared(){
    return (v.x*v.x)+(v.y*v.y)+(v.z*v.z);
}

};
