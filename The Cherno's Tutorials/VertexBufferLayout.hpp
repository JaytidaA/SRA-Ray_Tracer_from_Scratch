#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP

#include <vector>
#include <cassert>

#include <GL/glew.h>


struct vertex_Buffer_Element{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int get_size_of_type(unsigned int inputtype){
        switch(inputtype){
            case GL_FLOAT:          return sizeof(GLfloat); break;
            case GL_UNSIGNED_INT:   return sizeof(GLuint); break;
            case GL_INT:            return sizeof(GLint); break;
            case GL_UNSIGNED_BYTE:  return sizeof(GLbyte); break;
        }
        assert(false);
        return 0;
    }
};

class vertex_Buffer_Layout{
    private:
    std::vector<vertex_Buffer_Element> my_Elements;
    unsigned int my_Stride;

    public:
    vertex_Buffer_Layout():my_Stride(0){}
    ~vertex_Buffer_Layout(){}

    // Primary Templates
    template <typename T>
    void push(unsigned int count);

    inline const std::vector<vertex_Buffer_Element> & get_elements() const{ return my_Elements; }
    unsigned int get_stride() const{ return my_Stride; }
};

#endif //VERTEXBUFFERLAYOUT_HPP