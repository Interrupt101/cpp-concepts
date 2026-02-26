#include <glad/glad.h>   // GLAD must be included BEFORE GLFW
#include <GLFW/glfw3.h>
#include <iostream>

// Callback: called whenever the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Input processing
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Vertex shader source (as a C string)
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;  // Input: vertex position

    void main() {
        // gl_Position is the built-in output: clip-space position
        gl_Position = vec4(aPos, 1.0);
    }
)";

// Fragment shader source
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;  // Output: RGBA color

    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);  // Orange
    }
)";

int main() {
    // --- 1. Initialize GLFW ---
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Request OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // macOS requires this:
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // --- 2. Create a window ---
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello OpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Make this window's context current on this thread
    glfwMakeContextCurrent(window);

    // Register resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // --- 3. Initialize GLAD ---
    // GLAD loads OpenGL function pointers from the driver
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Set the initial viewport
    glViewport(0, 0, 800, 600);

    // Three vertices of a triangle (x, y, z)
    float vertices[] = {
       -0.5f, -0.5f, 0.0f,  // bottom-left
        0.5f, -0.5f, 0.0f,  // bottom-right
        0.0f,  0.5f, 0.0f   // top-center
    };

    /*
    VBO = actual vertex data (numbers)
    VAO = how to read those numbers
    */

    // Vertex Array Object — remembers how to interpret vertex data
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);  // Start recording

    // Vertex Buffer Object — stores raw vertex data on the GPU
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Upload vertices to GPU (STATIC_DRAW = uploaded once, used many times)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret the buffer:
    glVertexAttribPointer(
        0,                  // attribute location
        3,                  // number of values (x,y,z)
        GL_FLOAT,           // data type
        GL_FALSE,           // normalize?
        3 * sizeof(float),  // stride
        (void*)0            // offset
    );

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);  // Unbind VAO (stop recording)

    // Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex shader error:\n" << infoLog << "\n";
    }

    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Link into a shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Shaders are now baked into the program; delete the individual ones
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // --- 4. Render loop ---
    while (!glfwWindowShouldClose(window)) {
        // Handle input
        processInput(window);

        // Clear the screen to a dark teal color
        glClearColor(0.1f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // In the render loop:
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);  // Draw 3 vertices as 1 triangle

        // Swap front/back buffers (double buffering)
        glfwSwapBuffers(window);

        // Poll events (keyboard, mouse, window events)
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}