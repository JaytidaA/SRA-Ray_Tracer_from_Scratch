#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>


struct shaderProgramSource{
	std::string shaderVertexSource;
	std::string shaderFragmentSource;
};

// Farse file into different shader strings.
static shaderProgramSource parse_file(const std::string&);

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
	my_Window = glfwCreateWindow(640, 640, "Video 11: OpenGL Uniforms", NULL, NULL);
	if(!my_Window){ glfwTerminate(); return -1; }

   	// Make the window's context current
	glfwMakeContextCurrent(my_Window);

	glfwSwapInterval(1);

	if(glewInit() != GLEW_OK){ std::cout << "Error!" << std::endl; return -1;  }

	float positions[] = {
		-0.5f, -0.5f,	//0
		 0.5f, -0.5f,	//1
		 0.5f,  0.5f,	//2
		-0.5f,  0.5f	//3
	};

	unsigned int my_BufferIdx;
	glGenBuffers(1, &my_BufferIdx);
	glBindBuffer(GL_ARRAY_BUFFER, my_BufferIdx);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0,
	};

	unsigned int my_IboIdx;	//Ibo = Index Buffer Object
	glGenBuffers(1, &my_IboIdx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_IboIdx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);
	glEnableVertexAttribArray(0);


	shaderProgramSource shader_Source = parse_file("../res/shaders/basic.shader");

	unsigned int my_Shader = create_shader(shader_Source.shaderVertexSource, shader_Source.shaderFragmentSource);
	glUseProgram(my_Shader);


	// Get an unsigned int for the uniform in the same way as we get Buffer Ids or shader Ids.
	int location = glGetUniformLocation(my_Shader, "u_Colour");
	assert((location != -1));
	float r = 0.0f, increment = 0.01f;

	// Loop until the user closes the window
	while(!glfwWindowShouldClose(my_Window)){	
		//Render here
		glClear(GL_COLOR_BUFFER_BIT);

		// We send need to send 4 floats to vec4
		glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		if(r > 1.0f) increment = -0.001f;
		else if(r < 0.0f) increment = 0.001f;

		r += increment;

        	// Swap front and back buffers
        	glfwSwapBuffers(my_Window);

        	// Poll for and process events
        	glfwPollEvents();
	}

	glDeleteProgram(my_Shader);
	glfwTerminate();

	return 0;
}

static shaderProgramSource parse_file(const std::string& filepath){
	enum class shader_Type{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];
	shader_Type type = shader_Type::NONE;

	while(getline(stream, line)){
		if(line.find("# Shader") != std::string::npos){
			if(line.find("Vertex") != std::string::npos){
				type = shader_Type::VERTEX;
			}
			else if(line.find("Fragment") != std::string::npos){
				type = shader_Type::FRAGMENT;
			}
		}
		else{
			ss[(int)type] << line << "\n";
		}
	}

	stream.close();
	return {ss[0].str(), ss[1].str()};
}

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
