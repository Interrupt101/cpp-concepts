#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#define ASSERT(x) if (!(x)) __debugbreak();

#define GLCall(x) \
    GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
// #x converts the function call into a string.

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);