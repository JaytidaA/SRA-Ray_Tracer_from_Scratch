#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>

#include <cassert>

#define GLCall(x) GL_clear_error();\
    x;\
    assert(GL_log_call(#x, __FILE__, __LINE__));


void GL_clear_error();
bool GL_log_call(const char *, const char *, int);

#endif //RENDERER_HPP