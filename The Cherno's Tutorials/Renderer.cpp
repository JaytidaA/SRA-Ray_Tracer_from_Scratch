#include "Renderer.hpp"
#include <iostream>

void GL_clear_error(){
    while(glGetError() != GL_NO_ERROR){ /* Do nothing */ }
}

bool GL_log_call(const char * function, const char * file, int line){
	GLenum error = glGetError();
    bool error_Flag = true;
	while(error != GL_NO_ERROR){
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ", " << line << std::endl;
		error = glGetError();
        error_Flag = false;
	}
    return error_Flag;
}