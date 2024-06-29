#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
	GLFWwindow * my_Window;
	
	//Initialise the Library
	if(!glfwInit()){ return -1; }

	//Create a Windowed mode Window and its OpenGL Context
	my_Window = glfwCreateWindow(640, 480, "Hello, world from JaytidaA", NULL, NULL);
	if(!my_Window){ glfwTerminate(); return -1; }

	// Make the window's context current
	glfwMakeContextCurrent(my_Window);

	if(glewInit() != GLEW_OK){ std::cout << "Error!" << std::endl; return -1;  }
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Loop until the user closes the window
	while(!glfwWindowShouldClose(my_Window)){	
		//Render here
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();

        	// Swap front and back buffers
        	glfwSwapBuffers(my_Window);

        	// Poll for and process events
        	glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
