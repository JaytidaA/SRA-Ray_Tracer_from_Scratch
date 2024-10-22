#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>

int main()
{
	if(!glfwInit()){ throw std::runtime_error("Failed to initialize the GLFW library"); }
	
	GLFWwindow * my_Window = glfwCreateWindow(1920, 1080, "Le Title", NULL, NULL);
	if(!my_Window){ throw std::runtime_error("Failed to create an OpenGL Context"); }

	glfwMakeContextCurrent(my_Window);

	
	GLfloat vertices[] = {
		 0.0f, 0.1f,
		 0.5f, 0.0f,
		-0.5f, 0.0f
	};

	GLuint my_VBO;
	glGenBuffers(1, &my_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, my_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	std::string vertex_shader = "#version 330 core\n"
	"layout (location = 0) in vec2 aPos;\n"
	"void main(){ gl_Position = vec4(aPos.x, aPos.y, 1.0, 1.0); }";
	const char * vs = vertex_shader.c_str();

	GLuint my_VtxShader;
	my_VtxShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(my_VtxShader, 1, &vs, NULL);
	glCompileShader(my_VtxShader);

	std::string fragment_shader = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main(){ FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }";
	const char * fs = fragment_shader.c_str();

	GLuint my_FrgShader;
	my_FrgShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(my_FrgShader, 1, &fs, NULL);
	glCompileShader(my_FrgShader);

	GLuint my_Shader;
	my_Shader = glCreateProgram();
	glAttachShader(my_Shader, my_VtxShader);
	glAttachShader(my_Shader, my_FrgShader);
	glLinkProgram(my_Shader);
	glUseProgram(my_Shader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);


	while(!glfwWindowShouldClose(my_Window))
	{
		// Keep running
		glBindBuffer(GL_ARRAY_BUFFER, my_VBO);
		glUseProgram(my_Shader);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwPollEvents(); // Missing this
		glfwSwapBuffers(my_Window); // Swap the buffers
	}

	glfwDestroyWindow(my_Window);
	glfwTerminate();
	return 0;
}
