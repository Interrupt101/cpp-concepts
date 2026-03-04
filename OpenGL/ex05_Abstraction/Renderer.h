#pragma once

class VertexArray;
class IndexBuffer;
class Shader;

#define ASSERT(x) if (!(x)) __debugbreak();

#define GLCall(x) \
    GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
// #x converts the function call into a string.

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void Clear() const;
    void SetClearColor(float r, float g, float b, float a) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, Shader& shader);
};