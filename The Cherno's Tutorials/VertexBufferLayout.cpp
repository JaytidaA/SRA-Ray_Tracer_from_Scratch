#include "VertexBufferLayout.hpp"

template <>
void vertex_Buffer_Layout::push<float>(unsigned int count){
    my_Elements.push_back({GL_FLOAT, count, GL_FALSE});
    my_Stride += count * vertex_Buffer_Element::get_size_of_type(GL_FLOAT);
}

template <>
void vertex_Buffer_Layout::push<unsigned int>(unsigned int count){
    my_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    my_Stride += count * vertex_Buffer_Element::get_size_of_type(GL_UNSIGNED_INT);
}

template <>
void vertex_Buffer_Layout::push<unsigned char>(unsigned int count){
    my_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    my_Stride += count * vertex_Buffer_Element::get_size_of_type(GL_UNSIGNED_BYTE);
}