#ifndef  EK_APPLICATION_HPP
#define  EK_APPLICATION_HPP

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ekGLUtils.hpp"
#include "ekShaderUtils.hpp"

class Application{
	private:
	GLFWwindow * my_Window;
	const int width, height;
	bool antialias;			//anti_alias

	unsigned int my_VBO;
	unsigned int my_IBO;
	unsigned int my_VAO;
	unsigned int my_Texture;
	unsigned int my_Program;
	unsigned int my_Compute;

	float        * vertices;
	unsigned int * indices ;
	shaderProgramSource shaders;

	public:
	Application(int, int, const char *);
	~Application();

	void init(float *, unsigned int *, const char *);
	void set_vertices_and_indices(float *, unsigned int *);
	void set_texture_and_shader  (const char *);
	void start_and_set_loop ();
};

Application::Application(int width, int height, const char * name): width(width), height(height)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if(!glfwInit())
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}

	my_Window = glfwCreateWindow(width, height, name, NULL, NULL);
	if(!my_Window)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(my_Window);
	glfwSwapInterval(1);
	std::cout << "OpenGL Version before GLEW: " << glGetString(GL_VERSION) << std::endl;

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(my_Window);
		glfwTerminate();
		throw std::runtime_error("Failed to initialise GLEW!");
	}
	std::cout << "Window and OpenGL context successfully created!" << std::endl;
}

void Application::set_vertices_and_indices(float * vert, unsigned int * ind)
{
	// Expanding the screen according to aspect ratio
	vertices = vert;
	float aspect_ratio = (float)width / height;
	for(int i = 0; i < 16; i++){
		if(i%4==0){ vertices[i] *= aspect_ratio; }
	}
	
	// Setting OpenGL Context Parameters
	ekGLCall(glGenBuffers(1, &my_VBO));
	ekGLCall(glBindBuffer(GL_ARRAY_BUFFER, my_VBO));
	ekGLCall(glBufferData(GL_ARRAY_BUFFER, 16*sizeof(float), vertices, GL_STATIC_DRAW));

	ekGLCall(glGenVertexArrays(1, &my_VAO));
	ekGLCall(glBindVertexArray(my_VAO));

	ekGLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void *)0));
	ekGLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, ((const void *)(sizeof(float) * 2))));
	ekGLCall(glEnableVertexAttribArray(0));
	ekGLCall(glEnableVertexAttribArray(1));

	indices = ind;
	ekGLCall(glGenBuffers(1, &my_IBO));
	ekGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_IBO));
	ekGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), indices, GL_STATIC_DRAW));
}
	
void Application::set_texture_and_shader(const char * filepath)
{
	// Texture
	GLenum texture_target = GL_TEXTURE_2D;
	ekGLCall(glGenTextures(1, &my_Texture));
	ekGLCall(glBindTexture(texture_target, my_Texture));
	ekGLCall(glTexImage2D(texture_target, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
	ekGLCall(glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, GL_REPEAT));
	ekGLCall(glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, GL_REPEAT));
	ekGLCall(glTexParameteri(texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	ekGLCall(glTexParameteri(texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	// Shaders
	shaders    = parse_file(filepath);
	my_Program = create_shader(shaders.shaderVertexSource, shaders.shaderFragmentSource);
	my_Compute = create_compute_shader(shaders.shaderComputeSource);
	ekGLCall(glUseProgram(my_Compute));
}

void Application::start_and_set_loop()
{
	int winDim[2];
	glfwGetFramebufferSize(my_Window, winDim, winDim + 1);
	ekGLCall(glViewport((winDim[0]-width)/2, (winDim[1]-height)/2, width, height));
	ekGLCall(glEnable(GL_DEPTH_TEST));
	ekGLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));  // Set the background to black

	// First Iteration of Compute Shader
	ekGLCall(glBindImageTexture(0, my_Texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8));
	ekGLCall(glUniform1i(glGetUniformLocation(my_Compute, "uTexture"), 0));
	ekGLCall(glDispatchCompute(std::ceil(width/16), std::ceil(height/16), 1));
	ekGLCall(glMemoryBarrier(GL_ALL_BARRIER_BITS));


	GLenum texture_target = GL_TEXTURE_2D;
	// Unbinding shit
	ekGLCall(glBindVertexArray(0));
	ekGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	ekGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	ekGLCall(glBindTexture(texture_target, 0));
	ekGLCall(glUseProgram(0));

	while(!glfwWindowShouldClose(my_Window)){
		ekGLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// Setting a constant Window Size
		glfwGetFramebufferSize(my_Window, winDim, winDim + 1);
		ekGLCall(glViewport((winDim[0]-width)/2, (winDim[1]-height)/2, width, height));

		// Compute Shader
		ekGLCall(glBindTexture(texture_target, my_Texture));
		ekGLCall(glUseProgram(my_Compute));
		ekGLCall(glUniform1i(glGetUniformLocation(my_Compute, "uTexture"), 0));
		ekGLCall(glDispatchCompute(std::ceil(width/16), std::ceil(height/16), 1));
		ekGLCall(glMemoryBarrier(GL_ALL_BARRIER_BITS));

		// Rebinding everything here
		ekGLCall(glUseProgram(my_Program));
		ekGLCall(glBindVertexArray(my_VAO));
		ekGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_IBO));
		ekGLCall(glUniform1i(glGetUniformLocation(my_Program, "uTexture"), 0));


		// Give a draw call
		ekGLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		glfwSwapBuffers(my_Window);
		glfwPollEvents();
	}

	ekGLCall(glDeleteProgram(my_Program));
	glfwTerminate();
}

void Application::init(float * vertices, unsigned int * indices, const char * filepath)
{
	set_vertices_and_indices(vertices, indices);
	set_texture_and_shader  (filepath);
}

Application::~Application()
{
	ekGLCall(glDeleteProgram(my_Program));
	ekGLCall(glDeleteProgram(my_Compute));
	ekGLCall(glDeleteTextures(1, &my_Texture));
	ekGLCall(glDeleteVertexArrays(1, &my_VAO));
	ekGLCall(glDeleteBuffers(1, &my_VBO));
	ekGLCall(glDeleteBuffers(1, &my_IBO));
}

#endif //EK_APPLICATION_HPP
