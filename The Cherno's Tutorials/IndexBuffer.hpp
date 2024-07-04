#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

class index_Buffer{
    private:
    unsigned int my_RendererID;
    unsigned int my_Count;

    public:
    index_Buffer(const unsigned int *, unsigned int);
    ~index_Buffer();

    void bind() const;
    void unbind() const;

    inline unsigned int get_count(){ return my_Count; }
};

#endif //INDEXBUFFER_HPP