#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


// Compile Shader Method
static unsigned int compile_shader(unsigned int, const std::string&);

// Create Shader method
static unsigned int create_shader(const std::string &, const std::string &);

int main()
{
	GLFWwindow * my_Window;
	
	//Initialise the Library
	if(!glfwInit()){ return -1; }

	//Create a Windowed mode Window and its OpenGL Context
	my_Window = glfwCreateWindow(640, 480, "Video 7: Red Triangle", NULL, NULL);
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

	std::string vertex_Shader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;\n"
		"void main(){\n"
		"	gl_Position = position;\n"
		"}\n";

	std::string fragment_Shader = 
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 colour;\n"
		"void main(){\n"
		"	colour = vec4(1.0, 0.0, 0.0, 1.0);\n"
		"}\n";

	unsigned int my_Shader = create_shader(vertex_Shader, fragment_Shader);
	glUseProgram(my_Shader);

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

	glDeleteProgram(my_Shader);
	glfwTerminate();

	return 0;
}

static unsigned int compile_shader(unsigned int type, const std::string& source){
	unsigned int id = glCreateShader(type);

	//Get a C-Style Character Array as the method to compile a Shader becomes easier.
	//Otherwise have the length of each string ready.
	const char * src = &source[0];
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error Handline code
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

static unsigned int create_shader(const std::string & vtx_Shader, const std::string & frg_Shader){
	unsigned int program = glCreateProgram();
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vtx_Shader);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, frg_Shader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
