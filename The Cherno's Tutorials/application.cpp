#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

	{
		float positions[] = {
		-0.5f, -0.5f,	//0
		 0.5f, -0.5f,	//1
		 0.5f,  0.5f,	//2
		-0.5f,  0.5f	//3
		};

		vertex_Array va;
		vertex_Buffer vb(positions, 4 * 2 * sizeof(float));

		vertex_Buffer_Layout layout;
		layout.push<float>(2);

		va.add_buffer(vb, layout);

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,
		};

		index_Buffer ibo(indices, 6); //Ibo = Index Buffer Object

		shader sh("res/shaders/basic.shader");
		sh.bind();


		// Unbinding shit
		va.unbind();
		vb.unbind();
		ibo.unbind();
		sh.unbind();

		// Get an unsigned int for the uniform in the same way as we get Buffer Ids or shader Ids.
		// This comment is no longer valid as I am now using a class system
		sh.set_uniform_4f("u_Colour", 0.8f, 0.3f, 0.8f, 1.0f);
		float r = 0.0f, increment = 0.01f;

		// Loop until the user closes the window
		while(!glfwWindowShouldClose(my_Window)){
			//Render here
			GLCall(glClear(GL_COLOR_BUFFER_BIT));


			//Rebinding everything here
			sh.bind();
			va.bind();
			ibo.bind();

			// We send need to send 4 floats to vec4
			sh.set_uniform_4f("u_Colour", r, 0.3f, 0.8f, 1.0f);
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			if(r > 1.0f) increment = -0.001f;
			else if(r < 0.0f) increment = 0.001f;

			r += increment;

        	// Swap front and back buffers
        	glfwSwapBuffers(my_Window);

        	// Poll for and process events
        	glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}
