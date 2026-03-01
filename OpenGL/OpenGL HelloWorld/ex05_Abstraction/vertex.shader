#version 330 core
layout (location = 0) in vec3 aPos; // The index that connects CPU-side vertex data to the shader input variable
uniform vec3 uOffset;

void main() {
    gl_Position = vec4(aPos + uOffset, 1.0);
}