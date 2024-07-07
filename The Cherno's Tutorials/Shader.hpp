#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

struct shaderProgramSource{
	std::string shaderVertexSource;
	std::string shaderFragmentSource;
};

class shader{
    private:
    std::string my_Filepath;
    unsigned int my_RendererID;
    
    public:
    shader(const std::string &);
    ~shader();

    void bind() const;
    void unbind() const;

    // Set Uniform
    void set_uniform_4f(const std::string &, float, float, float, float);

    private:
    shaderProgramSource parse_file(const std::string &);
    unsigned int compile_shader(unsigned int, const std::string &);
    unsigned int create_shader(const std::string & , const std::string &);

    int get_uniform_location(const std::string &);
};

#endif //SHADER_HPP