//#include "RT-API/include/Ray.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static unsigned int compile_shader(unsigned int type, const std::string& source){
	unsigned int id = glCreateShader(type);

	//Get a C-Style String as the method to compile a Shader becomes easier.
	//Otherwise have the length of each string ready.
	const char * src = &source[0];
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error Handling code
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE){
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char * message = (char *) alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile " << ((type == GL_VERTEX_SHADER)?"vertex":"fragment") << " shader: " << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

int main(){
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

	int width, height;
	glfwGetFramebufferSize(my_Window, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set the background to black

	std::string vertex_Shader = R"(
		#version 330 core
		layout (location = 0) in vec2 aPos;
		layout (location = 1) in vec2 aTexCoord;

		out vec2 TexCoord;

		void main()
		{
			gl_Position = vec4(aPos, 0.0, 1.0);
			TexCoord = aTexCoord;
		}
	)";

	std::string fragment_Shader = R"(
		#version 330 core
		out vec4 FragColor;
		in vec2 TexCoord;

		void main()
		{
			vec3 topColor = vec3(0.5, 0.7, 1.0);
			vec3 bottomColor = vec3(1.0, 1.0, 1.0);

			float t = TexCoord.y; //blend factor
			vec3 blendedColor = mix(bottomColor, topColor, t);
			FragColor = vec4(blendedColor, 1.0);
		}
	)";


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
	glGenBuffers(1, &my_BufferIndex);
	glBindBuffer(GL_ARRAY_BUFFER, my_BufferIndex);
	glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW);

	unsigned int my_VertexArrayObjectIndex;
	glGenVertexArrays(1, &my_VertexArrayObjectIndex);
	glBindVertexArray(my_VertexArrayObjectIndex);

	unsigned int my_IndexBufferObjectIndex;
	glGenBuffers(1, &my_IndexBufferObjectIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_IndexBufferObjectIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void *)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, ((const void *)(sizeof(float) * 2)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	unsigned int my_Program = glCreateProgram();
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_Shader);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_Shader);
	glAttachShader(my_Program, vs);
	glAttachShader(my_Program, fs);
	glLinkProgram(my_Program);
	glValidateProgram(my_Program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glUseProgram(my_Program);

	// Unbinding shit
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);

	while(!glfwWindowShouldClose(my_Window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rebinding everything here
		glUseProgram(my_Program);
		glBindVertexArray(my_VertexArrayObjectIndex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_IndexBufferObjectIndex);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(my_Window);
		glfwPollEvents();
	}

	glDeleteProgram(my_Program);
	glfwTerminate();
	return 0;
}
