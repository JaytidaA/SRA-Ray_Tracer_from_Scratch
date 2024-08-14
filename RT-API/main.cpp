#include "include/Ray.hpp"
#include <iostream>
#include <GL/gl.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(){
	GLFWwindow * my_Window;

	// Initialise the Library
	if(!glfwinit()){ return -1; }

	// Create a Windowed mode window and its OpenGL Context
	my_Window = glfwCreateWindow(640, 640, "Raytracing with OpenGL", NULL, NULL);
	if(!my_Window){ glfwTerminate(); return -1; }

	// Make the window's context current
	glfwMakeContextCurrent(my_Window);
	glfwSwapInterval(1);
	if(glewInit() != GLEW_OK){ std::cout << "Error!\n"; return -1; }

	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(my_Window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, /* Add the number of triangles here */, GL_UNSIGNED_INT, nullptr);
		glfwSwapBuffers(my_Window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
