cmake_minimum_required(VERSION 3.10)
project(OpenGLExample)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(OpenGL_GL_PREFERENCE GLVND)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}:/usr/lib/x86_64-linux-gnu/cmake")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

include_directories(
    ${GLEW_INCLUDE_DIRS}
    /usr/include/GL
    /usr/include/glm
)

add_executable(OpenGLExample /home/rakshitha/Desktop/project/new.cpp)

target_link_libraries(OpenGLExample PRIVATE /usr/lib/x86_64-linux-gnu/libGLEW.so glfw3 OpenGL::GL dl)