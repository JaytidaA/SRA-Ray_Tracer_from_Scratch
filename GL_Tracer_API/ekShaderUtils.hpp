#ifndef EK_SHADER_UTILS_HPP
#define EK_SHADER_UTILS_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "ekGLUtils.hpp"

struct shaderProgramSource{
	std::string shaderVertexSource;
	std::string shaderFragmentSource;
};

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
	ekGLCall(unsigned int id = glCreateShader(type));

	//Get a C-Style String as the method to compile a Shader becomes easier.
	//Otherwise have the length of each string ready.
	const char * src = &source[0];
	ekGLCall(glShaderSource(id, 1, &src, nullptr));
	ekGLCall(glCompileShader(id));

	//Error Handling code
	int result;
	ekGLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if(result == GL_FALSE){
		int length;
		ekGLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char * message = (char *) alloca(length * sizeof(char));
		ekGLCall(glGetShaderInfoLog(id, length, &length, message));

		std::cout << "Failed to compile " << ((type == GL_VERTEX_SHADER)?"vertex":"fragment") << " shader: " << std::endl;
		std::cout << message << std::endl;
		ekGLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

static unsigned int create_shader(const std::string & vtx_Shader, const std::string & frg_Shader){
	ekGLCall(unsigned int program = glCreateProgram());
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vtx_Shader);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, frg_Shader);

	ekGLCall(glAttachShader(program, vs));
	ekGLCall(glAttachShader(program, fs));
	ekGLCall(glLinkProgram(program));
	ekGLCall(glValidateProgram(program));

	ekGLCall(glDeleteShader(vs));
	ekGLCall(glDeleteShader(fs));

	return program;
}

#endif //EK_SHADER_UTILS_HPP
