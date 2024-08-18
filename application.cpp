#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GL_Tracer_API/ekShaderUtils.hpp"

int main(int argc, char ** argv){
	if(argc != 2){ return -1; }

	// Request specific OpenGL version (3.3 Core)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * my_Window;

	// Initialize the library
	if(!glfwInit()){
		std::cerr << "Failed to initialize GLFW!" << std::endl;
		return -1;
	}

	// Create a windowed mode window and its OpenGL context
	my_Window = glfwCreateWindow(640, 640, "Raytracing with OpenGL", NULL, NULL);
	if(!my_Window){
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(my_Window);
	glfwSwapInterval(1);

	// Print OpenGL version before initializing GLEW
	std::cout << "OpenGL Version before GLEW: " << glGetString(GL_VERSION) << std::endl;

	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK){
		std::cerr << "Failed to initialize GLEW!" << std::endl;
		return -1;
	}
	std::cout << "Window and OpenGL context successfully created!" << std::endl;

	int maxUniforms;
	ekGLCall(glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &maxUniforms));
	std::cout << "Maximum numer of Uniforms are: " << maxUniforms << std::endl;

	int width, height;
	glfwGetFramebufferSize(my_Window, &width, &height);
	ekGLCall(glViewport(0, 0, width, height));

	ekGLCall(glEnable(GL_DEPTH_TEST));
	ekGLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));  // Set the background to black

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

	unsigned int my_BufferIndex;
	ekGLCall(glGenBuffers(1, &my_BufferIndex));
	ekGLCall(glBindBuffer(GL_ARRAY_BUFFER, my_BufferIndex));
	ekGLCall(glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW));

	unsigned int my_VertexArrayObjectIndex;
	ekGLCall(glGenVertexArrays(1, &my_VertexArrayObjectIndex));
	ekGLCall(glBindVertexArray(my_VertexArrayObjectIndex));

	unsigned int my_IndexBufferObjectIndex;
	ekGLCall(glGenBuffers(1, &my_IndexBufferObjectIndex));
	ekGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_IndexBufferObjectIndex));
	ekGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

	ekGLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void *)0));
	ekGLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, ((const void *)(sizeof(float) * 2))));
	ekGLCall(glEnableVertexAttribArray(0));
	ekGLCall(glEnableVertexAttribArray(1));

	shaderProgramSource ps = parse_file(argv[1]);
	unsigned int my_Program = create_shader(ps.shaderVertexSource, ps.shaderFragmentSource);
	ekGLCall(glUseProgram(my_Program));

	float randArray[10];
	for(int i = 0; i < 10; i++){ randArray[i] = ekRandomDouble(0, i); }
	ekGLCall(int uRandomFloats = glGetUniformLocation(my_Program, "prand"));
	if(uRandomFloats == -1){ std::cout << "Uniform not found. Exiting\n"; return -1; }
	ekGLCall(glUniform4fv(uRandomFloats, 10, randArray));

	// Unbinding shit
	ekGLCall(glBindVertexArray(0));
	ekGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	ekGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	ekGLCall(glUseProgram(0));

	while(!glfwWindowShouldClose(my_Window)){
		ekGLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// Setting a constant Window Size
		glfwGetFramebufferSize(my_Window, &width, &height);
		ekGLCall(glViewport(width/2 - 320, height/2 - 320, 640, 640));

		// Rebinding everything here
		ekGLCall(glUseProgram(my_Program));
		ekGLCall(glBindVertexArray(my_VertexArrayObjectIndex));
		ekGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_IndexBufferObjectIndex));

		// Set the Uniform Over Here
		for(int i = 0; i < 10; i++){ randArray[i] = ekRandomDouble(0, i); }
		ekGLCall(glUniform4fv(uRandomFloats, 10, randArray));
		
		// Give a draw call
		ekGLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		glfwSwapBuffers(my_Window);
		glfwPollEvents();
	}

	ekGLCall(glDeleteProgram(my_Program));
	glfwTerminate();
	return 0;
}
