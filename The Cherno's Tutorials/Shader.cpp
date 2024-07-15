#include "Shader.hpp"
#include "Renderer.hpp"

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

shader::shader(const std::string & filepath)
:my_Filepath(filepath), my_RendererID(0){
    shaderProgramSource shader_Source = parse_file(filepath);
	my_RendererID = create_shader(shader_Source.shaderVertexSource, shader_Source.shaderFragmentSource);
}

shader::~shader(){
    GLCall(glDeleteProgram(my_RendererID));
}

void shader::bind() const{
    GLCall(glUseProgram(my_RendererID));
}

void shader::unbind() const{
    GLCall(glUseProgram(0));
}

void shader::set_uniform_4f(const std::string & name, float v0, float v1, float v2, float v3){
	int location = get_uniform_location(name);
    glUniform4f(location, v0, v1, v2, v3);
}

void shader::set_uniform_mat_4f(const std::string & name, const glm::mat4 matrix, bool transpose){
	int location = get_uniform_location(name);
	glUniformMatrix4fv(location, 1, (transpose)?GL_TRUE:GL_FALSE, glm::value_ptr(matrix));
}

int shader::get_uniform_location(const std::string & name){
    int location;
	GLCall(location = glGetUniformLocation(my_RendererID, name.c_str()));
	if(location == -1)
        std::cout << "Warning: Uniform " <<  name << "does not exist!" << std::endl;
    
    return location;
}

unsigned int shader::compile_shader(unsigned int type, const std::string & source){
	unsigned int id = glCreateShader(type);

	//Get a C-Style String as the method to compile a Shader becomes easier.
	//Otherwise have the length of each string ready.
	const char * src = &source[0];
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	//Error Handling code
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if(result == GL_FALSE){
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char * message = (char *) alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));

		std::cout << "Failed to compile " << ((type == GL_VERTEX_SHADER)?"vertex":"fragment") << " shader: " << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

shaderProgramSource shader::parse_file(const std::string & filepath){
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

unsigned int shader::create_shader(const std::string & vtx_Shader, const std::string & frg_Shader){
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