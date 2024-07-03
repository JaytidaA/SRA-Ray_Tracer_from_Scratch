

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


#include <fstream>
#include <string>
#include <sstream>
struct ShaderSourceProgram 
{
    std::string vertexSource;
    std::string fragmentSource;
};
static struct ShaderSourceProgram ParseShader(const std::string filepath)
{
    enum class ShaderType
    {
        NONE=-1 , VERTEX=0, FRAGMENT=1
    };
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    ShaderType type=ShaderType::NONE;
    while(getline(stream,line))
    {
        if(line.find("#shader")!=std::string::npos)
        {
            if(line.find("vertex")!=std::string::npos)
            type=ShaderType::VERTEX;
            else if (line.find("fragment")!=std::string::npos)
            type=ShaderType::FRAGMENT;
        }
        else{
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(),ss[1].str()};
}
int maine()
{
    std::string filename = "/home/rudrakshi/opengl-project"; // Replace with your actual file path

    ShaderSourceProgram shader = ParseShader(filename);

    std::cout << "Vertex Shader Source:\n" << shader.vertexSource << "\n\n";
    std::cout << "Fragment Shader Source:\n" << shader.fragmentSource << "\n\n";

    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "rectangle!!", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   // glad: load all OpenGL function pointers
    // ---------------------------------------
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
      //  std::cout << "Failed to initialize GLAD" << std::endl;
        //return -1;
    //


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id= glCreateShader(type);
    const char* src= source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);
}
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program=glCreateProgram();
    unsigned int vs=CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs=CompileShader(GL_FRAGMENT_SHADER,fragmentShader);
    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

    

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // 0
         0.5f, -0.5f, 0.0f, // 1 
         0.5f,  0.5f, 0.0f, // 2  
         -0.5f,  0.5f, 0.0f// 3
        
    }; 
    unsigned int indices[]=
    {
        0,1,2,
        2,3,0
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int ibo;
    glGenBuffers(1,&ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,6*sizeof(unsigned int),indices,GL_STATIC_DRAW);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, nullptr);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}