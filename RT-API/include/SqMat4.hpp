#ifndef SQMAT4_HPP
#define SQMAT4_HPP

#include "Vec4.hpp"

class smat4{
	private:
	double el[4][4];
	// el[column-vec][row]

	public:
	smat4(double init = 0.0){
		for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(i == j){ el[i][j] = init; }
			else{ el[i][j] = 0; }
		}}
	}

	smat4(vec4 & c0, vec4 & c1, vec4 & c2, vec4 & c3){
		for(int i = 0; i < 4; i++){
			el[0][i] = (c0[i]);
			el[1][i] = (c1[i]);
			el[2][i] = (c2[i]);
			el[3][i] = (c3[i]);
		}
	}

	//TODO: Implement Matrix Multiplication with a Vector
	vec4 operator*(const vec4 &);
	smat4 operator*(const smat4 &);

	double * operator[](int);
};

#endif //SQMAT4_HPP
