#ifndef  SQMAT4HELPER_HPP
#define  SQMAT4HELPER_HPP

#include "SqMat4.hpp"

smat4 affine_translate(const vec4 & v){
	smat4 result(1.0);
	result[3][0] = v.x();
	result[3][1] = v.y();
	result[3][2] = v.z();
	result[3][3] = 1.0;
	return result;
}

#endif //SQMAT4HELPER_HPP
