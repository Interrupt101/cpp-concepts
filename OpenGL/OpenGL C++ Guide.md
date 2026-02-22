# OpenGL in C++: A Comprehensive Guide from Beginner to Advanced

> **Modern OpenGL (Core Profile 3.3+)** — Everything you need to build real-world graphics applications.

---

## Table of Contents

1. [What is OpenGL?](#1-what-is-opengl)
2. [Environment Setup](#2-environment-setup)
3. [Your First Window](#3-your-first-window)
4. [The Rendering Pipeline](#4-the-rendering-pipeline)
5. [Drawing Your First Triangle](#5-drawing-your-first-triangle)
6. [Shaders & GLSL](#6-shaders--glsl)
7. [Textures](#7-textures)
8. [Transformations & Math](#8-transformations--math)
9. [Coordinate Systems & Cameras](#9-coordinate-systems--cameras)
10. [Lighting](#10-lighting)
11. [Materials & Maps](#11-materials--maps)
12. [Model Loading](#12-model-loading)
13. [Framebuffers & Post-Processing](#13-framebuffers--post-processing)
14. [Advanced Techniques](#14-advanced-techniques)
15. [Project 1 — 3D Scene Viewer](#15-project-1--3d-scene-viewer)
16. [Project 2 — Physically Based Renderer](#16-project-2--physically-based-renderer)
17. [Project 3 — 2D Game Engine](#17-project-3--2d-game-engine)
18. [Performance & Best Practices](#18-performance--best-practices)
19. [Debugging OpenGL](#19-debugging-opengl)
20. [Next Steps](#20-next-steps)

---

## 1. What is OpenGL?

OpenGL (Open Graphics Library) is a cross-platform API for rendering 2D and 3D graphics using your GPU. It is not a library you download — it is a **specification** implemented by your GPU driver. You write C++ code that calls OpenGL functions; the driver translates them into GPU commands.

**Key facts:**
- OpenGL itself is just a spec. The actual implementation lives in your graphics driver (NVIDIA, AMD, Intel).
- **Core Profile** (3.3+) removes legacy "immediate mode" features. This guide uses core profile only.
- Alternatives include Vulkan (lower-level, more control), Metal (Apple), and Direct3D (Windows). OpenGL remains the best learning entry point.

### Why Modern OpenGL?

Old (legacy) OpenGL used `glBegin()`/`glEnd()` blocks. Modern OpenGL uses:
- **Vertex Buffer Objects (VBOs)** — upload geometry to the GPU once.
- **Vertex Array Objects (VAOs)** — record how to interpret that geometry.
- **Shader programs** — programmable GPU code in GLSL.

This approach is faster, more flexible, and reflects how all modern graphics APIs work.

---

## 2. Environment Setup

### Libraries You Need

| Library | Purpose |
|--------|---------|
| **GLFW** | Creates a window and OpenGL context, handles input |
| **GLAD** | Loads OpenGL function pointers at runtime |
| **GLM** | Math library (vectors, matrices) mirroring GLSL types |
| **stb_image** | Single-header image loader for textures |
| **Assimp** | (Advanced) 3D model loader |

### Installation — Windows (vcpkg)

```powershell
# Install vcpkg if you haven't
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg && bootstrap-vcpkg.bat

# Install dependencies
vcpkg install glfw3 glad glm stb assimp
vcpkg integrate install   # integrates with Visual Studio
```

### Installation — Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install build-essential cmake libglfw3-dev libglm-dev libassimp-dev

# Download GLAD from https://glad.dav1d.de/
# Settings: Language=C/C++, Specification=OpenGL, Profile=Core, Version=3.3
# Download the zip, copy glad.c and glad/glad.h to your project
```

### Installation — macOS

```bash
brew install cmake glfw glm assimp
# Download GLAD as above; macOS needs OpenGL 4.1 max (use version 4.1 on GLAD)
```

### CMakeLists.txt — Project Template

```cmake
cmake_minimum_required(VERSION 3.20)
project(OpenGLApp)

set(CMAKE_CXX_STANDARD 17)

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Add GLAD (manually included)
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# Your executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/shader.cpp
    src/camera.cpp
    src/mesh.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    include
    external/glad/include
    external/stb
)

target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
    glm::glm
    glad
)
```

### Recommended Project Structure

```
MyOpenGLApp/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── shader.cpp / shader.h
│   ├── camera.cpp / camera.h
│   ├── mesh.cpp   / mesh.h
│   └── model.cpp  / model.h
├── include/
│   └── (your headers)
├── shaders/
│   ├── basic.vert
│   └── basic.frag
├── assets/
│   ├── textures/
│   └── models/
└── external/
    ├── glad/
    └── stb/
```

---

## 3. Your First Window

### Creating a Window with GLFW

```cpp
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

    // --- 4. Render loop ---
    while (!glfwWindowShouldClose(window)) {
        // Handle input
        processInput(window);

        // Clear the screen to a dark teal color
        glClearColor(0.1f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front/back buffers (double buffering)
        glfwSwapBuffers(window);

        // Poll events (keyboard, mouse, window events)
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
```

**What just happened?**
- GLFW created an OS window with an OpenGL context attached.
- GLAD connected C++ function calls (like `glClearColor`) to the actual GPU driver code.
- The **render loop** runs every frame: clear → draw → swap → poll.
- **Double buffering**: you draw to a back buffer. When done, swap it to the front (visible). This prevents screen tearing.

---

## 4. The Rendering Pipeline

Understanding the pipeline is fundamental. Data flows from your CPU to pixels on screen:

```
CPU Memory
    │
    ▼
[Vertex Data] ──► Vertex Shader ──► Primitive Assembly
                                          │
                                          ▼
                               Geometry Shader (optional)
                                          │
                                          ▼
                               Rasterization (triangles → fragments)
                                          │
                                          ▼
                               Fragment Shader ──► Per-Fragment Tests
                                                         │
                                                         ▼
                                                   Framebuffer (screen)
```

**Stages you control with shaders:**

- **Vertex Shader** — runs once per vertex. Transforms 3D positions to clip space.
- **Fragment Shader** — runs once per screen pixel covered by a triangle. Outputs the final color.

**Stages handled automatically by OpenGL:**
- **Primitive Assembly** — connects vertices into triangles/lines/points.
- **Rasterization** — determines which pixels each triangle covers.
- **Depth Testing** — discards fragments hidden behind others.

---

## 5. Drawing Your First Triangle

This is the "Hello World" of OpenGL. It requires understanding three core objects: **VAO**, **VBO**, and a **shader program**.

### Vertex Data

OpenGL works in **Normalized Device Coordinates (NDC)**: x, y, z all in [-1, 1]. The center of the screen is (0, 0).

```cpp
// Three vertices of a triangle (x, y, z)
float vertices[] = {
   -0.5f, -0.5f, 0.0f,  // bottom-left
    0.5f, -0.5f, 0.0f,  // bottom-right
    0.0f,  0.5f, 0.0f   // top-center
};
```

### Uploading Data to the GPU

```cpp
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
// Attribute 0, 3 floats, not normalized, stride=12 bytes, offset=0
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

glBindVertexArray(0);  // Unbind VAO (stop recording)
```

**Understanding `glVertexAttribPointer`:**

```
glVertexAttribPointer(
    0,                // Attribute location (matches "layout(location=0)" in shader)
    3,                // Number of components per vertex (x, y, z = 3)
    GL_FLOAT,         // Data type of each component
    GL_FALSE,         // Should OpenGL normalize integer data? No.
    3 * sizeof(float),// Stride: byte distance between consecutive vertices
    (void*)0          // Offset: where does this attribute start in the buffer?
);
```

### Writing Shaders

Shaders are small programs written in **GLSL** (OpenGL Shading Language) and compiled at runtime.

```cpp
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
```

### Compiling & Linking Shaders

```cpp
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
```

### Drawing

```cpp
// In the render loop:
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glDrawArrays(GL_TRIANGLES, 0, 3);  // Draw 3 vertices as 1 triangle
```

### Using an Element Buffer Object (EBO) for Indexed Drawing

Instead of repeating shared vertices, use indices:

```cpp
float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top-right    (index 0)
     0.5f, -0.5f, 0.0f,  // bottom-right (index 1)
    -0.5f, -0.5f, 0.0f,  // bottom-left  (index 2)
    -0.5f,  0.5f, 0.0f   // top-left     (index 3)
};

unsigned int indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

unsigned int EBO;
glGenBuffers(1, &EBO);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// Draw with indices
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

---

## 6. Shaders & GLSL

### The Shader Class (Reusable)

Instead of embedding shader source in C++ strings, load from files:

**shader.h**
```cpp
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader() { glDeleteProgram(ID); }

    void use() const { glUseProgram(ID); }

    // Uniform setters
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& v) const;
    void setVec3(const std::string& name, const glm::vec3& v) const;
    void setVec4(const std::string& name, const glm::vec4& v) const;
    void setMat4(const std::string& name, const glm::mat4& m) const;

private:
    void checkCompileErrors(unsigned int shader, const std::string& type);
};
```

**shader.cpp**
```cpp
#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // Read files
    std::ifstream vFile(vertexPath), fFile(fragmentPath);
    std::stringstream vStream, fStream;
    vStream << vFile.rdbuf();
    fStream << fFile.rdbuf();
    std::string vertCode = vStream.str(), fragCode = fStream.str();
    const char* vSrc = vertCode.c_str(), *fSrc = fragCode.c_str();

    // Compile
    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vSrc, nullptr);
    glCompileShader(vert);
    checkCompileErrors(vert, "VERTEX");

    unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fSrc, nullptr);
    glCompileShader(frag);
    checkCompileErrors(frag, "FRAGMENT");

    // Link
    ID = glCreateProgram();
    glAttachShader(ID, vert);
    glAttachShader(ID, frag);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vert);
    glDeleteShader(frag);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setVec3(const std::string& name, const glm::vec3& v) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(v));
}
void Shader::setMat4(const std::string& name, const glm::mat4& m) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type) {
    int success; char log[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, log);
            std::cerr << "SHADER COMPILE ERROR [" << type << "]:\n" << log << "\n";
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, log);
            std::cerr << "PROGRAM LINK ERROR:\n" << log << "\n";
        }
    }
}
```

### GLSL Fundamentals

**Types:**

```glsl
float f = 1.0;
int i = 1;
bool b = true;

vec2 uv = vec2(0.5, 0.5);        // 2-component float vector
vec3 color = vec3(1.0, 0.0, 0.0); // RGB
vec4 pos = vec4(1.0, 2.0, 3.0, 1.0);

mat2 m2;  // 2x2 matrix
mat3 m3;  // 3x3 matrix
mat4 m4;  // 4x4 matrix (used for transforms)

sampler2D tex;     // 2D texture sampler
samplerCube cube;  // cubemap sampler
```

**Swizzling** — a powerful shorthand:

```glsl
vec4 v = vec4(1.0, 2.0, 3.0, 4.0);
vec3 xyz = v.xyz;     // (1, 2, 3)
vec2 zw  = v.zw;      // (3, 4)
vec3 rrr = v.rrr;     // (1, 1, 1) — rgba aliases xyzw
vec3 bgr = v.bgr;     // (3, 2, 1) — can reorder!
```

**Uniforms** — values passed from CPU to GPU:

```glsl
// In shader:
uniform float time;
uniform vec3 lightPos;
uniform mat4 model;
uniform sampler2D texture1;
```

```cpp
// In C++:
shader.use();
shader.setFloat("time", (float)glfwGetTime());
shader.setVec3("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
```

**Built-in functions:**

```glsl
float d = dot(a, b);        // Dot product
vec3 n = normalize(v);      // Unit vector
vec3 r = reflect(I, N);     // Reflection vector
float x = clamp(v, 0.0, 1.0);
vec3 c = mix(a, b, 0.5);    // Linear interpolation
float s = smoothstep(0.0, 1.0, t); // Smooth Hermite interpolation
vec4 color = texture(tex, uv);     // Sample a texture
```

### Passing Data Between Stages

Use `in`/`out` to pass data from vertex → fragment shader:

```glsl
// Vertex shader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
```

```glsl
// Fragment shader
#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;

void main() {
    FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
}
```

---

## 7. Textures

### Loading a Texture

Use `stb_image.h` (single-header, include once with `#define STB_IMAGE_IMPLEMENTATION`):

```cpp
// In ONE .cpp file:
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int loadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nChannels;
    // Flip vertically: OpenGL expects origin at bottom-left
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);

    if (data) {
        GLenum format = (nChannels == 1) ? GL_RED :
                        (nChannels == 3) ? GL_RGB : GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);  // Auto-generate mip levels

        // Wrapping (what happens outside [0,1])
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        std::cerr << "Failed to load texture: " << path << "\n";
    }

    stbi_image_free(data);
    return textureID;
}
```

### Texture Units

OpenGL has multiple **texture units** (usually 16+). Bind textures to units, then tell shaders which unit to sample from:

```cpp
// Bind textures to units
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture1);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, texture2);

// Tell shader which units to use
shader.use();
shader.setInt("texture1", 0);  // sampler2D texture1 = texture unit 0
shader.setInt("texture2", 1);  // sampler2D texture2 = texture unit 1
```

### Texture Parameters Reference

```cpp
// Wrap modes
GL_REPEAT          // tile
GL_MIRRORED_REPEAT // tile but mirror each time
GL_CLAMP_TO_EDGE   // stretch the edge pixel
GL_CLAMP_TO_BORDER // fill with a border color

// Filter modes (minification = smaller on screen)
GL_NEAREST                 // pixelated (nearest texel)
GL_LINEAR                  // bilinear filtering (smooth)
GL_LINEAR_MIPMAP_LINEAR    // trilinear (best quality, use with mipmaps)

// Border color (used with GL_CLAMP_TO_BORDER)
float borderColor[] = {1.0f, 0.0f, 0.0f, 1.0f};
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
```

---

## 8. Transformations & Math

### GLM (OpenGL Mathematics)

GLM mirrors GLSL types in C++:

```cpp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Vectors
glm::vec3 pos(1.0f, 2.0f, 3.0f);
glm::vec3 dir = glm::normalize(glm::vec3(0.5f, -1.0f, 0.2f));
float d = glm::dot(a, b);
glm::vec3 c = glm::cross(a, b);

// Matrices
glm::mat4 identity(1.0f);  // 4x4 identity matrix

// Transformations
glm::mat4 T = glm::translate(identity, glm::vec3(1.0f, 0.0f, 0.0f));
glm::mat4 R = glm::rotate(identity, glm::radians(45.0f), glm::vec3(0,0,1));
glm::mat4 S = glm::scale(identity, glm::vec3(2.0f, 2.0f, 1.0f));

// Combine: order matters! Scale, then rotate, then translate (right-to-left)
glm::mat4 model = T * R * S;
```

### The MVP Transform

Every vertex goes through three transforms to reach the screen:

```
Local Space ──[Model]──► World Space ──[View]──► Camera Space ──[Projection]──► Clip Space
```

```cpp
// Model: places the object in the world
glm::mat4 model = glm::mat4(1.0f);
model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

// View: positions the camera (we move the world, not the camera)
glm::mat4 view = glm::lookAt(
    glm::vec3(0.0f, 0.0f, 3.0f),  // Camera position
    glm::vec3(0.0f, 0.0f, 0.0f),  // Look-at target
    glm::vec3(0.0f, 1.0f, 0.0f)   // Up vector
);

// Projection: creates perspective (things farther away appear smaller)
glm::mat4 projection = glm::perspective(
    glm::radians(45.0f),     // Field of view (FOV)
    800.0f / 600.0f,         // Aspect ratio (width / height)
    0.1f,                    // Near plane (don't clip too close)
    100.0f                   // Far plane (don't render too far)
);

shader.setMat4("model", model);
shader.setMat4("view", view);
shader.setMat4("projection", projection);
```

**In the vertex shader:**
```glsl
gl_Position = projection * view * model * vec4(aPos, 1.0);
```

---

## 9. Coordinate Systems & Cameras

### The Camera Class

```cpp
// camera.h
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;    // Horizontal rotation (degrees)
    float Pitch;  // Vertical rotation (degrees)
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;   // Field of view

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f))
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
          MovementSpeed(2.5f), MouseSensitivity(0.1f), Zoom(45.0f),
          WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)), Yaw(-90.0f), Pitch(0.0f) {
        Position = position;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() const {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void ProcessKeyboard(CameraMovement direction, float deltaTime) {
        float velocity = MovementSpeed * deltaTime;
        if (direction == CameraMovement::FORWARD)  Position += Front * velocity;
        if (direction == CameraMovement::BACKWARD) Position -= Front * velocity;
        if (direction == CameraMovement::LEFT)     Position -= Right * velocity;
        if (direction == CameraMovement::RIGHT)    Position += Right * velocity;
        if (direction == CameraMovement::UP)       Position += WorldUp * velocity;
        if (direction == CameraMovement::DOWN)     Position -= WorldUp * velocity;
    }

    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true) {
        xOffset *= MouseSensitivity;
        yOffset *= MouseSensitivity;
        Yaw   += xOffset;
        Pitch += yOffset;
        if (constrainPitch) Pitch = glm::clamp(Pitch, -89.0f, 89.0f);
        updateCameraVectors();
    }

    void ProcessMouseScroll(float yOffset) {
        Zoom = glm::clamp(Zoom - yOffset, 1.0f, 90.0f);
    }

private:
    void updateCameraVectors() {
        // Recalculate front vector from Euler angles
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};
```

### Integrating Camera Input

```cpp
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 400, lastY = 300;
bool firstMouse = true;

// Mouse callback
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) { lastX = xpos; lastY = ypos; firstMouse = false; }
    float xOffset = xpos - lastX, yOffset = lastY - ypos; // Note: y-inverted
    lastX = xpos; lastY = ypos;
    camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    camera.ProcessMouseScroll((float)yOffset);
}

// In main():
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // Capture mouse
glfwSetCursorPosCallback(window, mouse_callback);
glfwSetScrollCallback(window, scroll_callback);

// In render loop:
float deltaTime = currentFrame - lastFrame;  // time between frames

if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);

glm::mat4 view = camera.GetViewMatrix();
glm::mat4 projection = glm::perspective(
    glm::radians(camera.Zoom), (float)width / height, 0.1f, 100.0f
);
```

---

## 10. Lighting

### Phong Lighting Model

The classic real-time lighting model has three components:

- **Ambient** — base light, simulates indirect illumination (constant).
- **Diffuse** — light scattered on rough surfaces (depends on angle to light).
- **Specular** — mirror-like highlights (depends on angle to viewer).

```glsl
// Fragment shader — Phong lighting
#version 330 core

in vec3 FragPos;    // World-space position
in vec3 Normal;     // World-space normal
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    // --- Ambient ---
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // --- Diffuse ---
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // --- Specular ---
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;

    // --- Combine ---
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
```

### Transforming Normals Correctly

Normals must be transformed differently from positions (non-uniform scaling breaks them):

```glsl
// In vertex shader:
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;  // = transpose(inverse(mat3(model)))

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = normalMatrix * aNormal;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
```

```cpp
// In C++:
glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
shader.setMat3("normalMatrix", normalMatrix);
```

### Multiple Light Types

**Directional Light** (sun — parallel rays, no position):

```glsl
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return ambient + diffuse + specular;
}
```

**Point Light** (bulb — decays with distance):

```glsl
struct PointLight {
    vec3 position;
    float constant;   // Attenuation factors
    float linear;
    float quadratic;
    vec3 ambient, diffuse, specular;
};

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                                light.quadratic * distance * distance);

    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular) * attenuation;
}
```

**Spot Light** (flashlight — cone):

```glsl
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;       // Inner cone angle (cos)
    float outerCutOff;  // Outer cone angle (cos)
    vec3 ambient, diffuse, specular;
    float constant, linear, quadratic;
};

// Smooth spotlight falloff
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // ... (same as point light but multiply by intensity)
}
```

---

## 11. Materials & Maps

### Material Struct in GLSL

```glsl
struct Material {
    sampler2D diffuse;    // Base color texture
    sampler2D specular;   // Specular intensity map (white = shiny, black = matte)
    sampler2D normal;     // Normal map (RGB encodes surface normals)
    sampler2D emission;   // Glowing areas
    float shininess;      // Specular exponent (8=matte, 256=shiny, 2048=mirror)
};
uniform Material material;
```

### Normal Mapping

Normal maps encode per-pixel surface normals in tangent space (red=X, green=Y, blue=Z), allowing flat polygons to appear detailed.

```glsl
// Fragment shader with normal mapping
vec3 normal = texture(material.normal, TexCoords).rgb;
normal = normalize(normal * 2.0 - 1.0);  // Convert [0,1] → [-1,1]
// Transform from tangent space to world space using TBN matrix
normal = normalize(TBN * normal);
```

**Calculating TBN matrix in vertex shader:**

```glsl
in vec3 aTangent;
in vec3 aBitangent;

// In main():
vec3 T = normalize(vec3(model * vec4(aTangent, 0.0)));
vec3 N = normalize(vec3(model * vec4(aNormal, 0.0)));
T = normalize(T - dot(T, N) * N);  // Re-orthogonalize
vec3 B = cross(N, T);
mat3 TBN = mat3(T, B, N);
```

### Shadow Mapping

The classic technique for rendering shadows:

**Pass 1 — Render scene from light's perspective, save depths:**

```cpp
// Create depth framebuffer
unsigned int depthMapFBO, depthMap;
glGenFramebuffers(1, &depthMapFBO);
glGenTextures(1, &depthMap);
glBindTexture(GL_TEXTURE_2D, depthMap);
glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0,
             GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
float border[] = {1.0f, 1.0f, 1.0f, 1.0f};
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);

glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
glDrawBuffer(GL_NONE);  // No color output needed
glReadBuffer(GL_NONE);
glBindFramebuffer(GL_FRAMEBUFFER, 0);
```

**Pass 2 — Render scene normally, compare depths:**

```glsl
// In main fragment shader:
float shadow = 0.0;
vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;  // Perspective divide
projCoords = projCoords * 0.5 + 0.5;  // Map to [0,1]

// PCF (Percentage Closer Filtering) for soft shadows
vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
for(int x = -1; x <= 1; ++x) {
    for(int y = -1; y <= 1; ++y) {
        float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
        shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
    }
}
shadow /= 9.0;
```

---

## 12. Model Loading

### Assimp

Use Assimp to load `.obj`, `.fbx`, `.gltf`, and many other 3D formats.

**mesh.h**

```cpp
#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "shader.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;   // "texture_diffuse", "texture_specular", etc.
    std::string path;
};

class Mesh {
public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> verts, std::vector<unsigned int> inds,
         std::vector<Texture> texs);

    void Draw(const Shader& shader) const;

private:
    unsigned int VBO, EBO;
    void setupMesh();
};
```

**mesh.cpp — setupMesh**

```cpp
void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    // Position (location 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, Position));
    // Normal (location 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, Normal));
    // TexCoords (location 2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, TexCoords));
    // Tangent (location 3)
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, Tangent));

    glBindVertexArray(0);
}
```

**model.h — Model using Assimp**

```cpp
#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"

class Model {
public:
    Model(const std::string& path) { loadModel(path); }
    void Draw(const Shader& shader) const;

private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat,
                          aiTextureType type, const std::string& typeName);
};
```

**model.cpp — key method**

```cpp
void Model::loadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate |        // Convert to triangles
        aiProcess_GenSmoothNormals |   // Calculate normals
        aiProcess_FlipUVs |            // Flip for OpenGL
        aiProcess_CalcTangentSpace     // Calculate tangent/bitangent
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << "\n";
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}
```

---

## 13. Framebuffers & Post-Processing

A framebuffer is a collection of buffers (color, depth, stencil) that you can render to off-screen.

### Creating a Framebuffer

```cpp
// Create framebuffer
unsigned int FBO;
glGenFramebuffers(1, &FBO);
glBindFramebuffer(GL_FRAMEBUFFER, FBO);

// Create color texture attachment
unsigned int colorTexture;
glGenTextures(1, &colorTexture);
glBindTexture(GL_TEXTURE_2D, colorTexture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0,
             GL_RGB, GL_UNSIGNED_BYTE, nullptr);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                       GL_TEXTURE_2D, colorTexture, 0);

// Create depth+stencil renderbuffer
unsigned int RBO;
glGenRenderbuffers(1, &RBO);
glBindRenderbuffer(GL_RENDERBUFFER, RBO);
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                          GL_RENDERBUFFER, RBO);

if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::cerr << "Framebuffer incomplete!\n";

glBindFramebuffer(GL_FRAMEBUFFER, 0);
```

### Post-Processing Render Loop

```cpp
// Pass 1: Render scene to off-screen framebuffer
glBindFramebuffer(GL_FRAMEBUFFER, FBO);
glEnable(GL_DEPTH_TEST);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
renderScene();

// Pass 2: Render the texture to a screen quad with a post-process shader
glBindFramebuffer(GL_FRAMEBUFFER, 0);
glDisable(GL_DEPTH_TEST);
glClear(GL_COLOR_BUFFER_BIT);

postProcessShader.use();
glBindVertexArray(quadVAO);
glBindTexture(GL_TEXTURE_2D, colorTexture);
glDrawArrays(GL_TRIANGLES, 0, 6);
```

### Post-Process Effects in GLSL

```glsl
// Grayscale
void main() {
    vec4 color = texture(screenTexture, TexCoords);
    float gray = dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
    FragColor = vec4(vec3(gray), 1.0);
}

// Invert
void main() {
    FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
}

// Kernel convolution (sharpen, blur, edge detection)
const float kernel[9] = float[](
    -1, -1, -1,
    -1,  9, -1,
    -1, -1, -1   // Sharpen kernel
);

void main() {
    vec2 offsets[9];
    float offset = 1.0 / 300.0;
    offsets[0] = vec2(-offset,  offset);
    // ... fill all 9 offsets
    vec3 color = vec3(0.0);
    for(int i = 0; i < 9; i++)
        color += vec3(texture(screenTexture, TexCoords + offsets[i])) * kernel[i];
    FragColor = vec4(color, 1.0);
}
```

---

## 14. Advanced Techniques

### Bloom

1. Render the scene normally.
2. Extract bright pixels (luminance > threshold) into a separate texture.
3. Blur that texture with a two-pass Gaussian blur (horizontal then vertical).
4. Add (additive blend) the blurred bright texture onto the original scene.

```glsl
// Brightness extraction fragment shader
void main() {
    vec3 color = texture(hdrBuffer, TexCoords).rgb;
    float brightness = dot(color, vec3(0.2126, 0.7152, 0.0722));
    brightColor = brightness > 1.0 ? vec4(color, 1.0) : vec4(0.0, 0.0, 0.0, 1.0);
}

// Gaussian blur (horizontal pass)
uniform bool horizontal;
float weight[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
void main() {
    vec2 texOffset = 1.0 / textureSize(image, 0);
    vec3 result = texture(image, TexCoords).rgb * weight[0];
    if(horizontal) {
        for(int i = 1; i < 5; ++i) {
            result += texture(image, TexCoords + vec2(texOffset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(texOffset.x * i, 0.0)).rgb * weight[i];
        }
    } else { /* vertical */ }
    FragColor = vec4(result, 1.0);
}
```

### HDR & Tone Mapping

When rendering with HDR (16-bit float buffers), you need to map back to [0,1] for display:

```glsl
// Reinhard tone mapping
vec3 mapped = hdrColor / (hdrColor + vec3(1.0));

// Exposure tone mapping (adjust this live with a slider!)
uniform float exposure;
vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);

// Apply gamma correction
const float gamma = 2.2;
mapped = pow(mapped, vec3(1.0 / gamma));
FragColor = vec4(mapped, 1.0);
```

### Deferred Shading

Forward rendering reruns lighting for every light on every fragment. Deferred shading separates geometry from lighting:

**GBuffer pass** — store geometry data into multiple textures:
```
gPosition  | World-space positions
gNormal    | World-space normals
gAlbedoSpec| Diffuse RGB + specular A
```

**Lighting pass** — sample GBuffer, run all lights in a single full-screen pass.

```cpp
// GBuffer setup
unsigned int gBuffer, gPosition, gNormal, gAlbedoSpec;
glGenFramebuffers(1, &gBuffer);
glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

// Position
glGenTextures(1, &gPosition);
glBindTexture(GL_TEXTURE_2D, gPosition);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, nullptr);
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

// Normal
glGenTextures(1, &gNormal);
glBindTexture(GL_TEXTURE_2D, gNormal);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, nullptr);
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

// Albedo + Specular
glGenTextures(1, &gAlbedoSpec);
glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);

unsigned int attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
glDrawBuffers(3, attachments);
```

### Instanced Rendering

Draw thousands of objects with a single draw call:

```cpp
// Store per-instance transforms in a buffer
std::vector<glm::mat4> modelMatrices(10000);
// ... fill with positions

unsigned int instanceVBO;
glGenBuffers(1, &instanceVBO);
glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
glBufferData(GL_ARRAY_BUFFER, 10000 * sizeof(glm::mat4), modelMatrices.data(), GL_STATIC_DRAW);

// A mat4 takes 4 attribute slots (each slot = vec4)
for (unsigned int i = 0; i < 4; i++) {
    glEnableVertexAttribArray(3 + i);
    glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                          (void*)(i * sizeof(glm::vec4)));
    glVertexAttribDivisor(3 + i, 1);  // Update per-instance, not per-vertex
}

// Draw 10000 instances with ONE call
glDrawArraysInstanced(GL_TRIANGLES, 0, meshVertexCount, 10000);
```

### Cubemaps & Skyboxes

```cpp
unsigned int loadCubemap(const std::vector<std::string>& faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (unsigned int i = 0; i < 6; i++) {
        int w, h, nCh;
        unsigned char* data = stbi_load(faces[i].c_str(), &w, &h, &nCh, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
                         w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    return textureID;
}
```

```glsl
// Skybox vertex shader — remove translation from view matrix
void main() {
    vec4 pos = projection * mat4(mat3(view)) * vec4(aPos, 1.0);
    gl_Position = pos.xyww;  // Force z=1.0 (always behind everything)
}

// Skybox fragment shader
uniform samplerCube skybox;
in vec3 TexCoords;
void main() {
    FragColor = texture(skybox, TexCoords);
}
```

---

## 15. Project 1 — 3D Scene Viewer

Build a complete 3D viewer with model loading, lighting, shadows, and camera controls.

### Architecture

```
SceneViewer/
├── src/
│   ├── main.cpp          ← Application entry point
│   ├── scene.h/cpp       ← Manages objects, lights
│   ├── renderer.h/cpp    ← Orchestrates rendering passes
│   ├── camera.h/cpp      ← FPS camera
│   ├── model.h/cpp       ← Assimp model loading
│   ├── mesh.h/cpp        ← GPU mesh data
│   └── shader.h/cpp      ← Shader wrapper
├── shaders/
│   ├── shadow_depth.vert/frag   ← Shadow map pass
│   ├── pbr.vert/frag            ← Main lighting pass
│   ├── skybox.vert/frag         ← Background
│   └── postprocess.vert/frag    ← HDR + bloom
```

### Core Render Loop

```cpp
void Renderer::render(const Scene& scene, const Camera& camera) {
    // --- Pass 1: Shadow Map ---
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    shadowShader.use();
    shadowShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
    scene.renderAllMeshes(shadowShader);

    // --- Pass 2: Scene to HDR Framebuffer ---
    glViewport(0, 0, scrWidth, scrHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pbrShader.use();
    pbrShader.setMat4("view", camera.GetViewMatrix());
    pbrShader.setMat4("projection", projection);
    pbrShader.setVec3("camPos", camera.Position);
    pbrShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, depthMap);
    pbrShader.setInt("shadowMap", 0);

    for (auto& [model, transform] : scene.models)
        model.Draw(pbrShader);

    renderSkybox(camera);

    // --- Pass 3: Bloom blur ---
    bloomBlur(brightTexture);

    // --- Pass 4: Tone mapping + final output ---
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    tonemapShader.use();
    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, hdrColorBuffer);
    glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, bloomBlurBuffer);
    renderQuad();
}
```

---

## 16. Project 2 — Physically Based Renderer

PBR (Physically Based Rendering) produces realistic materials using the microfacet BRDF theory.

### PBR Concepts

- **Albedo** — base color (no lighting baked in).
- **Metallic** — 0=dielectric (plastic), 1=metal.
- **Roughness** — 0=mirror smooth, 1=fully diffuse.
- **AO (Ambient Occlusion)** — pre-baked shadowing in crevices.

### Cook-Torrance BRDF

```glsl
// PBR fragment shader (simplified)
#version 330 core

const float PI = 3.14159265359;

// Normal Distribution Function (Trowbridge-Reitz GGX)
float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float NdotH = max(dot(N, H), 0.0);
    float denom = NdotH * NdotH * (a * a - 1.0) + 1.0;
    return (a * a) / (PI * denom * denom);
}

// Geometry Function (Smith's method with Schlick-GGX)
float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;
    return NdotV / (NdotV * (1.0 - k) + k);
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    return GeometrySchlickGGX(max(dot(N,V),0.0), roughness) *
           GeometrySchlickGGX(max(dot(N,L),0.0), roughness);
}

// Fresnel (Schlick approximation)
vec3 FresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main() {
    vec3 albedo    = pow(texture(albedoMap, TexCoords).rgb, vec3(2.2));
    float metallic = texture(metallicMap, TexCoords).r;
    float roughness= texture(roughnessMap, TexCoords).r;
    float ao       = texture(aoMap, TexCoords).r;

    vec3 N = getNormalFromMap();
    vec3 V = normalize(camPos - WorldPos);

    // Base reflectivity F0 (0.04 for non-metals)
    vec3 F0 = mix(vec3(0.04), albedo, metallic);

    vec3 Lo = vec3(0.0);
    for(int i = 0; i < 4; ++i) {
        vec3 L = normalize(lightPositions[i] - WorldPos);
        vec3 H = normalize(V + L);
        float dist = length(lightPositions[i] - WorldPos);
        float attenuation = 1.0 / (dist * dist);
        vec3 radiance = lightColors[i] * attenuation;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);
        float G   = GeometrySmith(N, V, L, roughness);
        vec3  F   = FresnelSchlick(max(dot(H, V), 0.0), F0);

        vec3  kD = (vec3(1.0) - F) * (1.0 - metallic);
        vec3  numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N,V),0.0) * max(dot(N,L),0.0) + 0.0001;
        vec3  specular = numerator / denominator;

        float NdotL = max(dot(N, L), 0.0);
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }

    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;

    // HDR tonemapping + gamma
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));
    FragColor = vec4(color, 1.0);
}
```

---

## 17. Project 3 — 2D Game Engine

A minimal 2D game engine using OpenGL with a sprite renderer and basic physics.

### Sprite Renderer

```cpp
class SpriteRenderer {
public:
    SpriteRenderer(const Shader& shader);
    void DrawSprite(const Texture2D& texture, glm::vec2 position,
                    glm::vec2 size, float rotate, glm::vec3 color);
private:
    Shader shader;
    unsigned int quadVAO;
    void initRenderData();
};

void SpriteRenderer::DrawSprite(const Texture2D& texture, glm::vec2 pos,
                                 glm::vec2 size, float rot, glm::vec3 color) {
    shader.use();
    glm::mat4 model(1.0f);

    // Rotate around sprite center
    model = glm::translate(model, glm::vec3(pos + size * 0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-size * 0.5f, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader.setMat4("model", model);
    shader.setVec3("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
```

### Orthographic Projection for 2D

```cpp
// Set once (or when window resizes):
glm::mat4 projection = glm::ortho(
    0.0f, (float)SCREEN_WIDTH,   // left, right
    (float)SCREEN_HEIGHT, 0.0f,  // bottom, top (flipped for screen coords)
    -1.0f, 1.0f                  // near, far
);
shader.setMat4("projection", projection);
```

### Simple Collision Detection

```cpp
struct AABB {
    glm::vec2 position, size;

    bool collides(const AABB& other) const {
        return position.x < other.position.x + other.size.x &&
               position.x + size.x > other.position.x &&
               position.y < other.position.y + other.size.y &&
               position.y + size.y > other.position.y;
    }
};

struct Circle {
    glm::vec2 center;
    float radius;

    bool collides(const AABB& box) const {
        glm::vec2 closest = glm::clamp(center,
            box.position, box.position + box.size);
        return glm::distance(center, closest) < radius;
    }
};
```

---

## 18. Performance & Best Practices

### State Change Minimization

OpenGL state changes are expensive. **Sort draw calls** to minimize them:

```cpp
// Bad: switch shaders every draw
for (auto& obj : objects) {
    obj.shader.use();
    obj.mesh.draw();
}

// Good: batch by shader
for (auto& [shader, objects] : objectsByShader) {
    shader.use();
    for (auto& obj : objects)
        obj.mesh.draw();
}
```

**Rule of thumb for sort order:** Sort by (1) shader, (2) textures, (3) VAO.

### Frustum Culling

Don't draw objects outside the camera frustum:

```cpp
bool Frustum::isAABBVisible(const glm::vec3& min, const glm::vec3& max) const {
    for (const auto& plane : planes) {
        // Pick the positive vertex (furthest in direction of plane normal)
        glm::vec3 positive = min;
        if (plane.normal.x >= 0) positive.x = max.x;
        if (plane.normal.y >= 0) positive.y = max.y;
        if (plane.normal.z >= 0) positive.z = max.z;

        if (glm::dot(plane.normal, positive) + plane.d < 0)
            return false;  // Outside this plane
    }
    return true;
}
```

### Uniform Buffer Objects (UBO)

Share uniforms across multiple shaders without re-setting them:

```cpp
// Create UBO for matrices (shared by all shaders)
unsigned int uboMatrices;
glGenBuffers(1, &uboMatrices);
glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboMatrices);  // Binding point 0

// In shaders, declare a matching block:
// layout (std140, binding = 0) uniform Matrices {
//     mat4 projection;
//     mat4 view;
// };

// Update per frame:
glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
glBufferSubData(GL_UNIFORM_BUFFER, 0,               sizeof(glm::mat4), glm::value_ptr(projection));
glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
```

### Buffer Streaming (Dynamic Updates)

```cpp
// For frequently updated data (particles, UI), use streaming patterns
// Orphaning: discard old buffer, get new memory
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STREAM_DRAW);  // Orphan
glBufferData(GL_ARRAY_BUFFER, size, newData, GL_STREAM_DRAW);  // Upload

// Or use glBufferSubData for partial updates:
glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
```

### General Performance Tips

```
✓ Use VAOs — never set vertex format every frame.
✓ Use indexed drawing (EBO/glDrawElements) to halve vertex data.
✓ Generate mipmaps for all textures (GL_LINEAR_MIPMAP_LINEAR).
✓ Use GL_STATIC_DRAW for static geometry, GL_DYNAMIC_DRAW for changing data.
✓ Batch draw calls — many small draws kill performance.
✓ Enable back-face culling (glEnable(GL_CULL_FACE)) — skip back-facing triangles.
✓ Set depth test to GL_LEQUAL when drawing skyboxes (avoid z-fighting).
✓ Profile with RenderDoc, NSight, or PIX before optimizing.
✗ Don't call glGetError() in a hot loop (it flushes the pipeline).
✗ Don't use glFinish() unless you're measuring timing.
```

---

## 19. Debugging OpenGL

### OpenGL Debug Output (4.3+)

The best debugging tool — receive error messages directly from the driver:

```cpp
void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id,
    GLenum severity, GLsizei length, const char* message, const void* userParam)
{
    // Filter non-significant notifications
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cerr << "OpenGL Debug [" << id << "]: " << message << "\n";

    switch (source) {
    case GL_DEBUG_SOURCE_API:             std::cerr << "Source: API"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Source: Shader Compiler"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     std::cerr << "Source: Application"; break;
    }

    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:   std::cerr << " | Severity: HIGH\n"; break;
    case GL_DEBUG_SEVERITY_MEDIUM: std::cerr << " | Severity: Medium\n"; break;
    case GL_DEBUG_SEVERITY_LOW:    std::cerr << " | Severity: Low\n"; break;
    }
}

// Enable:
glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
// After gladLoadGL:
glEnable(GL_DEBUG_OUTPUT);
glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);  // Errors on the calling thread
glDebugMessageCallback(glDebugOutput, nullptr);
glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
```

### glGetError() — Manual Checking

```cpp
// Utility to check errors at specific points
GLenum err;
while ((err = glGetError()) != GL_NO_ERROR) {
    std::cerr << "OpenGL Error: 0x" << std::hex << err << "\n";
}

// Macro for easy insertion while developing:
#define GL_CHECK(stmt) do { stmt; \
    GLenum err = glGetError(); \
    if (err != GL_NO_ERROR) { \
        std::cerr << "OpenGL error " << err << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
    } \
} while(0)

// Usage:
GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, 3));
```

### RenderDoc — GPU Frame Capture

RenderDoc is a free, cross-platform GPU debugger. It lets you:
- Capture a single frame.
- Inspect every draw call.
- View the state of every texture, buffer, and shader at any point.
- See shader inputs/outputs per-pixel.

To enable RenderDoc programmatically:
```cpp
// Add RenderDoc API header and call capture from code
// Or simply launch your app through RenderDoc
```

### Common Mistakes

```
MISTAKE: Black screen
→ Check: Is depth testing turned on but not clearing GL_DEPTH_BUFFER_BIT?
→ Check: Are MVP matrices correct? Print gl_Position in vertex shader.
→ Check: Is the viewport set correctly?
→ Check: Is back-face culling removing your triangles (wrong winding order)?

MISTAKE: Texture shows as all-white or all-black  
→ Check: Is glActiveTexture called before glBindTexture?
→ Check: Is the sampler2D uniform set to the correct texture unit?
→ Check: Did stbi_load succeed? Always check the return value.
→ Check: Is stbi_set_flip_vertically_on_load(true) set?

MISTAKE: Shader doesn't compile
→ Always print the info log (glGetShaderInfoLog).
→ Check GLSL version matches your OpenGL version.

MISTAKE: Flickering/Z-fighting
→ Adjust near/far planes (don't use 0.001/10000).
→ Use a depth bias for shadow maps.
→ Use GL_POLYGON_OFFSET_FILL for overlapping surfaces.

MISTAKE: Memory leak
→ Always call glDelete* for every glGen*.
→ Delete shader sources after linking (glDeleteShader).
→ glfwDestroyWindow and glfwTerminate on exit.
```

---

## 20. Next Steps

### Topics to Explore After This Guide

**Rendering Techniques:**
- Screen Space Ambient Occlusion (SSAO)
- Screen Space Reflections (SSR)
- Cascaded Shadow Maps (for large scenes)
- Variance Shadow Maps
- Particle systems using transform feedback or compute shaders
- Skeletal animation (bone weights + inverse kinematics)

**Modern OpenGL (4.3+):**
- Compute Shaders — general purpose GPU computation (particles, physics, image processing)
- Direct State Access (DSA) — cleaner API, no need to bind before modifying
- Persistent mapped buffers — eliminate CPU/GPU synchronization stalls
- Sparse textures — virtual texturing for massive worlds

**Beyond OpenGL:**
- **Vulkan** — the next step. Explicit GPU control, no driver magic, massive parallelism.
- **WebGL/WebGPU** — OpenGL/Vulkan-like APIs in the browser.
- **Unity/Unreal** — production engines built on top of these APIs.

### Recommended Resources

| Resource | What For |
|---------|---------|
| [learnopengl.com](https://learnopengl.com) | The best free OpenGL tutorial site |
| *OpenGL SuperBible* (7th ed.) | Comprehensive reference book |
| *Real-Time Rendering* (4th ed.) | Theory behind all rendering techniques |
| [Shadertoy.com](https://shadertoy.com) | Experiment with GLSL shaders live |
| RenderDoc | Essential GPU frame debugger |
| [The Book of Shaders](https://thebookofshaders.com) | Deep GLSL and visual math |
| Khronos OpenGL Wiki | Official reference and spec |

### Final Checklist Before Shipping

```
□ Enable GL_DEBUG_OUTPUT during development
□ Remove glGetError() calls from hot paths in release
□ Generate mipmaps for all textures
□ Enable back-face culling (GL_CULL_FACE)
□ Use correct depth function (GL_LESS for most, GL_LEQUAL for skyboxes)
□ Match vertex attribute locations with layout(location=N) in shaders
□ Clean up all OpenGL objects on shutdown (glDeleteBuffers, glDeleteTextures, etc.)
□ Handle window resize (update viewport + projection matrix)
□ Use deltaTime for all movement (frame-rate independent)
□ Profile before optimizing — use RenderDoc or NVIDIA NSight
```

---

*This guide covers OpenGL 3.3 Core Profile through 4.3+ features. The core concepts — buffers, shaders, the MVP transform, lighting models — apply directly to Vulkan, Metal, and Direct3D as well. Master these fundamentals and any graphics API becomes approachable.*
