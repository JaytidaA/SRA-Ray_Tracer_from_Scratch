#include <GL/glew.h>
#include <iostream>
#include <cassert>

#ifndef  EKL_DEBUGGING
#define  EKL_DEBUGGING

#define eklGLCall(x) eklGLClearErrors();\
x;\
assert(eklGLLogCall(#x, __FILE__, __LINE__));

void eklGLClearErrors(){
	while(glGetError() != GL_NO_ERROR){}
}

bool eklGLLogCall(const char * fnname, const char * file, int line){
	GLenum signal = glGetError();
	bool error = false;
	while(signal != GL_NO_ERROR){
		#ifndef I_AM_NOT_DEBUGGING
			std::cout << "ERROR::OPENGL::" << line << "::" << file << " Oopsie Woopsie! You have made a fucky wucky! A wittle fucko boingo in the function " << fnname << std::endl;
		#else
			std::cout << "ERROR::OPENGL::" << line << "::" << file << " Error in command: " << fnname << std::endl;
		#endif


		error = true;
		signal = glGetError();
	}
	return !error;
}

#endif //EKL_DEBUGGING
