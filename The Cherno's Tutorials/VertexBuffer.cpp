#include "VertexBuffer.hpp"
#include "Renderer.hpp"

vertex_Buffer::vertex_Buffer(const void * data, unsigned int size){
    GLCall(glGenBuffers(1, &my_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, my_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

vertex_Buffer::~vertex_Buffer(){
    GLCall(glDeleteBuffers(1, &my_RendererID));
}

void vertex_Buffer::bind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, my_RendererID));
}

void vertex_Buffer::unbind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}