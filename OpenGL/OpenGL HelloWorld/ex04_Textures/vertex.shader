#version 330 core
layout (location = 0) in vec3 aPos;
uniform vec3 uOffset;

void main() {
    gl_Position = vec4(aPos + uOffset, 1.0);
}