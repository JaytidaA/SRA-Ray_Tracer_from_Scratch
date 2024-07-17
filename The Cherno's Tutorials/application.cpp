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
	my_Window = glfwCreateWindow(640, 640, "Pyramid!!!", NULL, NULL);
	if(!my_Window){ glfwTerminate(); return -1; }

   	// Make the window's context current
	glfwMakeContextCurrent(my_Window);

	glfwSwapInterval(1);

	if(glewInit() != GLEW_OK){ std::cout << "Error!" << std::endl; return -1;  }

    GLCall(glEnable(GL_DEPTH_TEST));

    {
        
        float positions[] = {
            0.0f,  0.5f,  0.0f,     // Apex
            1.0f, -0.5f,  1.0f,     // Base vertices
           -1.0f, -0.5f,  1.0f,
           -1.0f, -0.5f, -1.0f,
            1.0f, -0.5f, -1.0f,
        };

        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3,
            0, 3, 4,
            0, 4, 1,
            1, 2, 3,
            1, 3, 4
        };

        vertex_Buffer VB1(positions, 5 * 3 * sizeof(float));
        index_Buffer IBO1(indices, 6 * 3);

        vertex_Buffer_Layout VBL1;
        VBL1.push<float>(3);

        vertex_Array VA1;
        VA1.add_buffer(VB1, VBL1);

        shader SH1("res/shaders/rotator.shader");
        SH1.bind();
        SH1.set_uniform_4f("u_Colour", 1.0f, 1.0f, 0.0f, 0.7f);

        glm::vec3 camPos_Vector = glm::vec3(0.0f, 2.0f, 4.0f);
        glm::vec3 target_Vector = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up_Vector = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(camPos_Vector, target_Vector, up_Vector);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 640.0f / 640.0f, 0.1f, 100.0f);

        SH1.set_uniform_mat_4f("u_Model", model, false);
        SH1.set_uniform_mat_4f("u_View", view, false);
        SH1.set_uniform_mat_4f("u_Projection", projection, false);

        glm::mat4 transformation = glm::mat4(1.0f);
        SH1.set_uniform_mat_4f("u_Rotation", transformation, false);

        SH1.unbind();


        while(!glfwWindowShouldClose(my_Window)){
		    //Render here
	    	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
            
            IBO1.bind();

            transformation = glm::rotate(transformation, -0.05f, glm::vec3(0.0f, 0.1f, 0.0f));

            SH1.set_uniform_mat_4f("u_Rotation", transformation, false);

            SH1.bind();
		    GLCall(glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr));

            // Do something here

        	// Swap front and back buffers
            glfwSwapBuffers(my_Window);

    	    // Poll for and process events
            glfwPollEvents();
        }
    }

    glfwTerminate();
	return 0;
}