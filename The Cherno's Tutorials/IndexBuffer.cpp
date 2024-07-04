#include "IndexBuffer.hpp"
#include "Renderer.hpp"

index_Buffer::index_Buffer(const unsigned int * data, unsigned int count):
my_Count(count){
    GLCall(glGenBuffers(1, &my_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

index_Buffer::~index_Buffer(){
    GLCall(glDeleteBuffers(1, &my_RendererID));
}

void index_Buffer::bind() const{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_RendererID));
}

void index_Buffer::unbind() const{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}