#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <string>
#include <sstream>

// Vertex and Fragment Shader source code
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in int aFaceIndex;

flat out int faceIndex;
uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    faceIndex = aFaceIndex;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
flat in int faceIndex;
out vec4 FragColor;
uniform vec4 faceColors[5];

void main()
{
    FragColor = faceColors[faceIndex];
}
)";

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

unsigned int compileShader(unsigned int type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return shader;
}

int main() {
    // Initialize GLFW and configure
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Pyramid Rotation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Compile and link shader program
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Pyramid vertices and indices
    float vertices[] = {
        // positions         // face indices
        -0.5f, -0.5f, -0.5f, 0,
         0.5f, -0.5f, -0.5f, 0,
         0.5f, -0.5f,  0.5f, 0,
        -0.5f, -0.5f,  0.5f, 0,
         0.0f,  0.5f,  0.0f, 1,
         0.0f,  0.5f,  0.0f, 2,
         0.0f,  0.5f,  0.0f, 3,
         0.0f,  0.5f,  0.0f, 4
    };

    unsigned int indices[] = {
        // Base
        0, 1, 2,
        2, 3, 0,
        // Sides
        0, 1, 4,
        1, 2, 5,
        2, 3, 6,
        3, 0, 7
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind Vertex Array Object
    glBindVertexArray(VAO);

    // Copy vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Copy indices array in a buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribIPointer(1, 1, GL_INT, 4 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    float rotationAngle = 0.0f;

    // Colors for each face
    glm::vec4 faceColors[] = {
        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), // Red
        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), // Green
        glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), // Blue
        glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), // Yellow
        glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)  // Magenta
    };

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // Clear the colorbuffer and depthbuffer
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        // Use shader program
        glUseProgram(shaderProgram);

        // Update rotation angle
        rotationAngle += 0.01f;

        // Create transformation
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y axis

        // Get matrix's uniform location and set matrix
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        // Set colors for each face
        unsigned int faceColorsLoc = glGetUniformLocation(shaderProgram, "faceColors");
        glUniform4fv(faceColorsLoc, 5, glm::value_ptr(faceColors[0]));

        // Render the pyramid
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // De-allocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
