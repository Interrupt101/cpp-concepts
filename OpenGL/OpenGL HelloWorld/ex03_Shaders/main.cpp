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
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

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

        float time = glfwGetTime();
        float xOffset = sin(time) * 0.5f;

        shader.setVec3("uOffset", glm::vec3(0.0f, xOffset, 0.0f));
        shader.setVec4("uColor", glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window); 
        glfwPollEvents();
    }

    glfwTerminate();

    std::cout << "Hello World!\n";
}