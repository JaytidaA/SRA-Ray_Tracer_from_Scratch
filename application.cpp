#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GL_Tracer_API/ekShaderUtils.hpp"
#include "GL_Tracer_API/ekApplication.hpp"

int main(int argc, char ** argv){
	if(argc != 2){ return -1; }

	float vertices[] = {
		// positions   // texture coords
		-1.0f,  1.0f,  0.0f,  1.0f,
		-1.0f, -1.0f,  0.0f,  0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f
	};

	unsigned int indices[] = {
    		0, 1, 2,
    		2, 3, 0
	};

	try{
		Application app(640, 640, "Raytracing in OpenGL");
		app.init(vertices, indices, argv[1]);
		app.start_and_set_loop();
	} catch (const std::exception & e){
		std::cerr << "Error: " << e.what() << std::endl;
		return -1;
	}
	// Toggle Comment for Makefile */

	return 0;
}

