#include <GL/glew.h>
#include <iostream>
#include <cassert>


#ifdef I_AM_NOT_DEBUGGING
#define eklGLCall(x) x;
#else
#define eklGLCall(x) eklGLClearErrors();\
x;\
assert(eklGLLogCall(#x, __FILE__, __LINE__));
#endif

void eklGLClearErrors(){
	while(glGetError() != GL_NO_ERROR){}
}

bool eklGLLogCall(const char * fnname, const char * file, int line){
	GLenum signal = glGetError();
	bool error = false;
	while(signal != GL_NO_ERROR){
		std::cout << "ERROR::OPENGL::" << file << "::" << line << " Oopsie Woopsie! You have made a fucky wucky! A wittle fucko boingo in the function " << fnname << "\n";
		std::cout << "ERROR CODE::" << signal << std::endl;
		error = true;
		signal = glGetError();
	}
	return !error;
}
