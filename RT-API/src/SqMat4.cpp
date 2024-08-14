#include "../include/SqMat4.hpp"

vec4 smat4::operator*(const vec4 & w){
	vec4 v = w;
	double result[4] = {0, 0, 0, 0};
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			result[i] += v[j]*el[j][i];
	}}
	//result[i] = \sum_{i=0}^{3} v[j]*el[j][i]
	return vec4(result);
}

smat4 smat4::operator*(const smat4 & smat){
	smat4 sm = smat;
	vec4 w[4] = {vec4(sm[0]), vec4(sm[1]), vec4(sm[2]), vec4(sm[3])};
	for(int i = 0; i < 4; i++){
		w[i] = *(this) * w[i];
	}
	return smat4(w[0], w[1], w[2], w[3]);
}

double * smat4::operator[](int index){
	double *ret = el[index];
	return ret;
}
