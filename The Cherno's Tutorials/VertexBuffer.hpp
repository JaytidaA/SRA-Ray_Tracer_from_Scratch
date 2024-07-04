#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

class vertex_Buffer{
    private:
    unsigned int my_RendererID;

    public:
    vertex_Buffer(const void *, unsigned int);
    ~vertex_Buffer();

    void bind() const;
    void unbind() const;
};

#endif //VERTEXBUFFER_HPP