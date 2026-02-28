#include <glad/glad.h>   // GLAD must be included BEFORE GLFW
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"

int main()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Shaders in OpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }
    glViewport(0, 0, 800, 600);
    
    float vertices[] = {
        // rectangle 1 (left)
        -0.9f, -0.5f, 0.0f,  // 0
        -0.1f, -0.5f, 0.0f,  // 1
        -0.1f,  0.5f, 0.0f,  // 2
        -0.9f,  0.5f, 0.0f,  // 3

        // rectangle 2 (right)
         0.1f, -0.5f, 0.0f,  // 4
         0.9f, -0.5f, 0.0f,  // 5
         0.9f,  0.5f, 0.0f,  // 6
         0.1f,  0.5f, 0.0f   // 7
    };

    unsigned int indices[] = {
        // rect 1
        0, 1, 2,
        2, 3, 0,
        // rect 2
        4, 5, 6,
        6, 7, 4
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                  // attribute location
        3,                  // number of values (x,y,z)
        GL_FLOAT,           // data type
        GL_FALSE,           // normalize?
        3 * sizeof(float),  // stride
        (void*)0            // offset
    );

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    Shader shader("vertex.shader", "fragment.shader");


    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.use();
        glBindVertexArray(VAO);

        shader.setVec4("uColor", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        shader.setVec4("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));

        glfwSwapBuffers(window); 
        glfwPollEvents();
    }

    glfwTerminate();

    std::cout << "Hello World!\n";
}