#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Shader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"

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
        // position      // texCoord
        0.0f, 000.0f,    0.0f, 0.0f,  // 0
        0.0f, 200.0f,    0.0f, 1.0f,  // 1
        200.0f, 0.0f,    1.0f, 0.0f,  // 2
        200.0f, 200.0f,    1.0f, 1.0f   // 3
    };

    unsigned int indices[] = {
        // rect
        0, 1, 2,
        1, 2, 3
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // SRC - DESTINATION
    
    // Vertex Array Object
    VertexArray va;
    va.Bind();

    // Vertex Buffer Object
    VertexBuffer vb(vertices, sizeof(vertices));

    // Element Buffer Object (index)
    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

    VertexBufferLayout layout;
    layout.Push<float>(2); // position
    layout.Push<float>(2); // texture coords
    va.AddBuffer(vb, layout);

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

    Shader shader("vertex.shader", "fragment.shader");
    shader.use();

    shader.setMat4("u_MVP", proj);

    Texture texture("image.png");
    unsigned int slot = 0;
    texture.Bind(slot);

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        renderer.SetClearColor(0.1f, 0.15f, 0.15f, 1.0f);
        renderer.Clear();

        shader.setInt("u_Texture", slot);
        renderer.Draw(va, ib, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}