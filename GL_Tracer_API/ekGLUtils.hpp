#ifndef  EK_GL_UTILS_HPP
#define  EK_GL_UTILS_HPP

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <limits>
#include <GL/glew.h>

#define ekGLCall(x) \
	ekClearGLErrors();\
	x;\
	assert(ekGetGLErrors(#x, __FILE__, __LINE__));

void ekClearGLErrors(){ while(glGetError() != GL_NO_ERROR){/* Do nothing */} }

bool ekGetGLErrors(const char * function, const char * file, int line){
	GLenum error = glGetError();
	bool error_flag = true;
	while(error != GL_NO_ERROR){
		std::cout << "[OpenGL Error] (" << error << "): " << function << ", " << file << ", " << line << std::endl;
		error = glGetError();
		error_flag = false;
	}
	return error_flag;
}

inline double ekRandomDouble(){
	// Returns a random double in between [0, 1)
	return std::rand()/(RAND_MAX + 1.0);
}

inline double ekRandomDouble(double min, double max) {
	// Returns a random double in between [min, max)
	return min + (max - min)*ekRandomDouble();
}

#endif //EK_GL_UTILS_HPP
