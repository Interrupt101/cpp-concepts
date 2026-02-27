// a triangle that has a color that changes smoothly
#include <glad/glad.h>   // GLAD must be included BEFORE GLFW
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

// Callback: called whenever the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);
    if (!stream.is_open())
    {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
    }

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            if (type != ShaderType::NONE)
                ss[(int)type] << line << '\n';
        }
    }

    return {
        ss[0].str(),
        ss[1].str()
    };
}

unsigned int CompileShader(const char* shaderSource, GLenum shaderType)
{
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    // Check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader error:\n" << infoLog << "\n";
    }
    return shader;
}

int main()
{
    // --- 1. Initialize GLFW ---
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Request OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Set the initial viewport
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

        // rect 2 (same pattern, +4)
        4, 5, 6,
        6, 7, 4
    };

    // Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Element Buffer Object
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Tell OpenGL how to interpret the buffer:
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);


    ShaderProgramSource shaderSource = ParseShader("Basic.shader");
    // Compile vertex shader
    unsigned int vertexShader = CompileShader(shaderSource.VertexSource.c_str(), GL_VERTEX_SHADER);
    unsigned int fragmentShader = CompileShader(shaderSource.FragmentSource.c_str(), GL_FRAGMENT_SHADER);

    // Link into a shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex shader error:\n" << infoLog << "\n";
    }

    // Shaders are now baked into the program; delete the individual ones
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // --- 4. Render loop ---
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        int loc = glGetUniformLocation(shaderProgram, "uColor"); 
        glUniform4f(loc, 1, 0, 0, 1);   // red
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glUniform4f(loc, 0, 0, 1, 1);   // blue
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));

        // Swap front/back buffers (double buffering)
        glfwSwapBuffers(window);

        // Poll events (keyboard, mouse, window events)
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}
