#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "shader.h"
#include "Renderer.h"


/// <summary>
/// Removes any previous error so we don’t confuse old errors with new ones.
/// </summary>
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] ("
            << error << "): "
            << function << " "
            << file << ":"
            << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::SetClearColor(float r, float g, float b, float a) const
{
    GLCall(glClearColor(r, g, b, a));
}

void Renderer::Draw(const VertexArray& va, 
    const IndexBuffer& ib, 
    Shader& shader)
{
    shader.use();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}