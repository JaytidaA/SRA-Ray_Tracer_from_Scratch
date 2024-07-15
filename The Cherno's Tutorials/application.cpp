#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <cassert>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

int main()
{
	GLFWwindow * my_Window;
	
	//Initialise the Library
	if(!glfwInit()){ return -1; }

	//Create a Windowed mode Window and its OpenGL Context
	my_Window = glfwCreateWindow(640, 640, "Abstraction of Elements", NULL, NULL);
	if(!my_Window){ glfwTerminate(); return -1; }

   	// Make the window's context current
	glfwMakeContextCurrent(my_Window);

	glfwSwapInterval(1);

	if(glewInit() != GLEW_OK){ std::cout << "Error!" << std::endl; return -1;  }

    float positions[] = {
        0.0f,  0.0f,  0.5f,
        1.0f,  1.0f, -0.5f,
       -1.0f,  1.0f, -0.5f,
       -1.0f, -1.0f, -0.5f,
        1.0f, -1.0f, -0.5f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1,
        1, 2, 3,
        2, 3, 4
    };

    vertex_Buffer vb1(positions, 5 * 3 * sizeof(float));
    index_Buffer ibo1(indices, 6 * 3);

    vertex_Buffer_Layout vbl1;
    vbl1.push<float>(3);

    vertex_Array va1;
    va1.add_buffer(vb1, vbl1);

    shader sh1("res/shaders/basic.shader");
    sh1.set_uniform_4f("u_Colour", 1.0f, 1.0f, 0.0f, 0.7f);

    while(!glfwWindowShouldClose(my_Window)){
		//Render here
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

        sh1.set_uniform_4f("u_Colour", 1.0f, 1.0f, 0.0f, 0.7f);
		GLCall(glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr));

        // Do something here

    	// Swap front and back buffers
        glfwSwapBuffers(my_Window);

    	// Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
	return 0;
}