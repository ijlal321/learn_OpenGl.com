#include <iostream>
#include <glad/glad.h> 
// include GLAD before GLFW. The include file for GLAD includes the required OpenGL headers behind the scenes (like GL/gl.h)
// so be sure to include GLAD before other header files that require OpenGL (like GLFW).
#include <GLFW/glfw3.h>
#include "Shader.h"

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
    Shader ourShader("../../Shaders/shader.vs", "../../Shaders/shader.fs");

    // Time to create Triangle 1
    float vertices[] = {
        -0.5,  0.5,  0.0,   1.0, 0.0, 0.0,// left top
        -0.5, -0.5,  0.0,   0.0, 1.0, 0.0, // left bottom
         0.5,  0.5,  0.0,   0.0, 0.0, 1.0, // right top
         0.5, -0.5,  0.0,   0.0, 0.0, 0.0, // right bottom
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
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // No Dont Unbind when VOA is still bind. BCZ EBO is bnid to VAO, removing it while VBO is bind will cause issues

    glBindVertexArray(0);

    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)){

        // Input
        processInput(window);

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // (set state) set clear clolor buffer
        glClear(GL_COLOR_BUFFER_BIT); // (do something based on state) clear colors using clear color buffer

        ourShader.use();

        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
    
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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