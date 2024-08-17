#include <GL/glew.h>  
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, bool &showMenu, float &offsetX, float &offsetY);
 
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
 
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 vertices;\n"
    "uniform float size;\n"
    "uniform vec2 offset;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(size * vertices.x + offset.x, size * vertices.y + offset.y, size * vertices.z, 1.0);\n"
    "}\0";
 
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "   FragColor = color;\n"
    "}\n\0";
 
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
 
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ImGui!!!", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
 
    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
 
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
 
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
 
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
 
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
 
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 
 
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
 
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330");
 
    bool drawTriangle= true;
    float size = 1.0f; //size variation
    float color[4] = {0.8f,0.3f,0.02f,1.0f}; //color variation
    float offsetX = 0.0f, offsetY = 0.0f; // for position
    bool showMenu = false;  // to control menu visibility
 
    glUseProgram(shaderProgram);
    glUniform1f(glGetUniformLocation(shaderProgram,"size"),size);
    glUniform4f(glGetUniformLocation(shaderProgram,"color"), color[0],color[1],color[2],color[3]);
    glUniform2f(glGetUniformLocation(shaderProgram, "offset"), offsetX, offsetY);
 
    while (!glfwWindowShouldClose(window))
    {
        processInput(window, showMenu, offsetX, offsetY);  // Pass the showMenu reference
 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
 
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
 
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
 
        if(drawTriangle) // only render triangle if drawTriangle is true
          glDrawArrays(GL_TRIANGLES, 0, 3);
 
        if (showMenu)  // Only render ImGui menu if showMenu is true
        {
            ImGui::Begin("Hello, I am Rudrakshi");
            ImGui::Text("triangle");
            ImGui::Checkbox("draw triangle", &drawTriangle);
            ImGui::SliderFloat("Size",&size,1.0f,5.0f);
            ImGui::ColorEdit4("Color",color);
            ImGui::End();
        }
 
        glUseProgram(shaderProgram);
        glUniform1f(glGetUniformLocation(shaderProgram,"size"),size);
        glUniform4f(glGetUniformLocation(shaderProgram,"color"), color[0],color[1],color[2],color[3]);
        glUniform2f(glGetUniformLocation(shaderProgram, "offset"), offsetX, offsetY);
 
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
 
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
 
    glfwTerminate();
    return 0;
}
 
void processInput(GLFWwindow *window, bool &showMenu, float &offsetX, float &offsetY)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
 
    const float moveSpeed = 0.01f;
    // the object will move according to the arrow keys
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        offsetY += moveSpeed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        offsetY -= moveSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        offsetX -= moveSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        offsetX += moveSpeed;
 
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)  // menu is visible by pressing 'M' key
    {
        showMenu = !showMenu;
    }
}