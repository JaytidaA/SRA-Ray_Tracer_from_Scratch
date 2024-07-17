#include "VertexArray.hpp"
#include "Renderer.hpp"

vertex_Array::vertex_Array(){
	GLCall(glGenVertexArrays(1, &my_RendererID));
}

vertex_Array::~vertex_Array(){
    GLCall(glDeleteVertexArrays(1, &my_RendererID));
}

void vertex_Array::add_buffer(const vertex_Buffer & vb, const vertex_Buffer_Layout & vb_Layout){
    bind();
    vb.bind();
    const auto & elements = vb_Layout.get_elements();

    unsigned int offset = 0;

    for(unsigned int i = 0; i < elements.size(); i++){
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized,
                vb_Layout.get_stride(), (const void *)offset));

        offset += elements[i].count * vertex_Buffer_Element::get_size_of_type(elements[i].type);
    }
}

void vertex_Array::bind() const{
    GLCall(glBindVertexArray(my_RendererID));
}

void vertex_Array::unbind() const{
    GLCall(glBindVertexArray(0));
}