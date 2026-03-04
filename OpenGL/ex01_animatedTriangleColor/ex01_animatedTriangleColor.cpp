// a triangle that has a color that changes smoothly
#include <glad/glad.h>   // GLAD must be included BEFORE GLFW
#include <GLFW/glfw3.h>
#include <iostream>

// Callback: called whenever the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Vertex shader source (as a C string)
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";
// Fragment shader source
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;

    uniform vec4 ourColor;

    void main() {
        FragColor = ourColor;
    }
)";

unsigned int CompileShader(const char* shaderSource,  GLenum shaderType)
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

    // Three vertices of a triangle (x, y, z)
    float vertices[] = {
       -0.5f, -0.5f, 0.0f,  
        0.5f, -0.5f, 0.0f, 
        0.0f,  0.5f, 0.0f  
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


    // Compile vertex shader
    unsigned int vertexShader = CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

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

        float timeValue = glfwGetTime();
        // Create value between 0 and 1 using sine
        float mixValue = (sin(timeValue) / 2.0f) + 0.5f;
        // Red increases, Blue decreases
        float red = mixValue;
        float blue = 1.0f - mixValue;

        int colorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(colorLocation, red, 0.0f, blue, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front/back buffers (double buffering)
        glfwSwapBuffers(window);

        // Poll events (keyboard, mouse, window events)
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}
