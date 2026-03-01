#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

int main()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello OpenGL", nullptr, nullptr);
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
    
    // Vertex Array Object
    VertexArray va;
    va.Bind();

    // Vertex Buffer Object
    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    va.AddBuffer(vb, layout);

    Shader shader("vertex.shader", "fragment.shader");

    Renderer renderer;
    while (!glfwWindowShouldClose(window)) {
        renderer.SetClearColor(0.1f, 0.15f, 0.15f, 1.0f);
        renderer.Clear();

        renderer.Draw(va, ib, shader);
        //GLCall(shader.setVec4("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
        //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        //GLCall(shader.setVec4("uColor", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
        //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)) ));

        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

    glfwTerminate();

	return 0;
}