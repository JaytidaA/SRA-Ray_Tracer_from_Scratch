#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <glHelpers/ErrorChecking.hpp>
#include <inc/eklVector.hpp>
#include <inc/eklRay.hpp>

#include <iostream>
#include <stdexcept>

int main()
{
	if(!glfwInit()){ throw std::runtime_error("Failed to initialise the GLFW Library!\n"); }

	GLFWwindow * my_Window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if(my_Window == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to Create a Window\n");
	}

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(my_Window);

	glfwSwapInterval(1);

	if(glewInit() != GLEW_OK)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to initialise the Extension Wrangler!\n");
	}


	GLfloat vertices[] = {
		 1.0f,  1.0f,
		-1.0f,  1.0f,
		 1.0f, -1.0f,
	};

	GLuint triangle;
	eklGLCall(glGenBuffers(1, &triangle));
	eklGLCall(glBindBuffer(GL_ARRAY_BUFFER, triangle));
	eklGLCall(glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW));

	GLuint vao;
	eklGLCall(glGenVertexArrays(1, &vao));
	eklGLCall(glBindVertexArray(vao));

	eklGLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (const void *)0));
	eklGLCall(glEnableVertexAttribArray(0));

	const char * vtx_src = "#version 330 core\n"
	"layout (location=0) in vec2 position;\n"
	"out vec2 fragpos;\n"
	"void main(){ gl_Position = vec4(position, 0.0, 1.0); fragpos = position; }\0";

	const char * frg_src = "#version 330 core\n"
	"in vec2 fragpos;\n"
	"out vec4 colour;\n"
	"void main(){\n"
	"\tvec4 blue = vec4(0.5, 0.7, 1.0, 1.0); vec4 white = vec4(1.0, 1.0, 1.0, 1.0);\n"
	"\tfloat y = fragpos.y * 0.5 + 0.5;\n"
	"\t//float y = 2 * fragpos.y;\n"
	"\tcolour = y * white + (1.0 - y) * blue;\n"
	"}\0";
	
	eklGLCall(GLuint program = glCreateProgram());
	eklGLCall(GLuint vs = glCreateShader(GL_VERTEX_SHADER));
	eklGLCall(glShaderSource(vs, 1, &vtx_src, nullptr));
	eklGLCall(glCompileShader(vs));
	eklGLCall(GLuint fs = glCreateShader(GL_FRAGMENT_SHADER));
	eklGLCall(glShaderSource(fs, 1, &frg_src, nullptr));
	eklGLCall(glCompileShader(fs));

	eklGLCall(glAttachShader(program, vs));
	eklGLCall(glAttachShader(program, fs));
	eklGLCall(glLinkProgram(program));
	eklGLCall(glValidateProgram(program));

	eklGLCall(glDeleteShader(vs));
	eklGLCall(glDeleteShader(fs));

	eklGLCall(glUseProgram(program));

	eklGLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

	GLuint num_vertex_shader, num_fragment_shader;
	eklGLCall(glGenQueries(1, &num_vertex_shader));
	eklGLCall(glGenQueries(1, &num_fragment_shader));

	while(!glfwWindowShouldClose(my_Window))
	{
		// Begin Querying for the number of times the Vertex and Fragment Shaders have been called
		eklGLCall(glBeginQuery(GL_VERTEX_SHADER_INVOCATIONS, num_vertex_shader));
		eklGLCall(glBeginQuery(GL_FRAGMENT_SHADER_INVOCATIONS, num_fragment_shader));

		eklGLCall(glClear(GL_COLOR_BUFFER_BIT));

		eklGLCall(glDrawArrays(GL_TRIANGLES, 0, 6));

		// End Querying for the number of times the Vertex and the Fragment Shaders have been called
		eklGLCall(glEndQuery(GL_VERTEX_SHADER_INVOCATIONS));
		eklGLCall(glEndQuery(GL_FRAGMENT_SHADER_INVOCATIONS));

		glfwSwapBuffers(my_Window);
		glfwPollEvents();
	}

	GLint times_vtx, times_frg;
	GLint wait[2] = {GL_FALSE, GL_FALSE};
	int times = 0;
	
	while((wait[0] == GL_FALSE) && (wait[1] == GL_FALSE)){
		eklGLCall(glGetQueryObjectiv(num_vertex_shader, GL_QUERY_RESULT_AVAILABLE, wait));
		eklGLCall(glGetQueryObjectiv(num_fragment_shader, GL_QUERY_RESULT_AVAILABLE, wait+1));
		times++;
	}

	eklGLCall(glGetQueryObjectiv(num_vertex_shader, GL_QUERY_RESULT, &times_vtx));
	eklGLCall(glGetQueryObjectiv(num_fragment_shader, GL_QUERY_RESULT, &times_frg));
	glfwTerminate();

	std::cout << "In every iteration, the vertex   shader was run " << times_vtx << " times!\n";
	std::cout << "In every iteration, the fragment shader was run " << times_frg << " times!\n";
	std::cout << "To get the results of the queries, we had to wait " << times << " (" << times-1 << "(actual) + 1(mandatory)) times.\n";
	return 0;
}
