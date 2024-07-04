#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
	GLFWwindow * my_Window;
	
	//Initialise the Library
	if(!glfwInit()){ return -1; }

	//Create a Windowed mode Window and its OpenGL Context
	my_Window = glfwCreateWindow(640, 480, "Video 4", NULL, NULL);
	if(!my_Window){ glfwTerminate(); return -1; }

   	// Make the window's context current
	glfwMakeContextCurrent(my_Window);

	if(glewInit() != GLEW_OK){ std::cout << "Error!" << std::endl; return -1;  }

	float positions[] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	unsigned int my_BufferIdx;
	glGenBuffers(1, &my_BufferIdx);
	glBindBuffer(GL_ARRAY_BUFFER, my_BufferIdx);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);
	glEnableVertexAttribArray(0);

	// Loop until the user closes the window
	while(!glfwWindowShouldClose(my_Window)){	
		//Render here
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

        	// Swap front and back buffers
        	glfwSwapBuffers(my_Window);

        	// Poll for and process events
        	glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
