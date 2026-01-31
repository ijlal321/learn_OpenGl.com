#include <iostream>
#include <glad/glad.h> 
// include GLAD before GLFW. The include file for GLAD includes the required OpenGL headers behind the scenes (like GL/gl.h)
// so be sure to include GLAD before other header files that require OpenGL (like GLFW).
#include <GLFW/glfw3.h>

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.5f, 0.5f, 1.0f);\n"
    "}\n\0";

int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#if defined(__APPLE__) && defined (__MACH__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGl", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }   
    
    // to adjust opengl viewport when size of window changes - also called on startup
    glfwSetFramebufferSizeCallback(
        window, 
        [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height); // callback function to call when window size changes
        });



        
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // create shader program 2
    unsigned int vertex_shader2 = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment_shader2 = glCreateShader(GL_FRAGMENT_SHADER);


    glShaderSource(vertex_shader2, 1, &vertexShaderSource, NULL);
    glShaderSource(fragment_shader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(vertex_shader2);
    glCompileShader(fragment_shader2);

    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertex_shader2);
    glAttachShader(shaderProgram2, fragment_shader2);
    glLinkProgram(shaderProgram2);

    glDeleteShader(vertex_shader2);
    glDeleteShader(fragment_shader2);

    // glCreateShader()

    // Time to create Triangle 1
    float vertices[] = {
        -0.5,  0.5,  0.0, // left top
        -0.5, -0.5,  0.0, // left bottom
         0.5,  0.5,  0.0, // right top
        //  0.5, -0.5,  0.0, // right bottom
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3,
    };

    

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // No Dont Unbind when VOA is still bind. BCZ EBO is bnid to EBO, removing it while VBO is bind will cause issues

    glBindVertexArray(0);

    // triangle2
    float vertices2[] = {
         0.5,  0.5,  0.0, // right top
         0.5, -0.5,  0.0, // right bottom
        -0.5, -0.5,  0.0, // left bottom
    };
    unsigned int VBO2, VAO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO2);
        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
        glEnableVertexAttribArray(0);

        
    
    glBindVertexArray(0);

    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)){

        // Input
        processInput(window);

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // (set state) set clear clolor buffer
        glClear(GL_COLOR_BUFFER_BIT); // (do something based on state) clear colors using clear color buffer

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    
        glUseProgram(shaderProgram2);
        
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}