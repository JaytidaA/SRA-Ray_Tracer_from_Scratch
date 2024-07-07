#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class vertex_Array{
    private:
    unsigned int my_RendererID;

    public:
    vertex_Array();
    ~vertex_Array();

    void add_buffer(const vertex_Buffer &, const vertex_Buffer_Layout &);

    void bind() const;
    void unbind() const;
};

#endif //VERTEXARRAY_HPP