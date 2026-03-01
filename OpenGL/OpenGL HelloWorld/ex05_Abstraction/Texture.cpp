// Texture.cpp
#include "Texture.h"

#include <glad/glad.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& path)
    : m_RendererID(0),
    m_FilePath(path),
    m_LocalBuffer(nullptr),
    m_Width(0),
    m_Height(0),
    m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);

    m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
    if (!m_LocalBuffer)
    {
        std::cerr << "Failed to load texture: " << m_FilePath << "\n";
        return;
    }

    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    // Texture parameters
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    // Upload texture (force RGBA = 4 channels)
    GLCall(glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA8,
        m_Width, m_Height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer
    ));

    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    stbi_image_free(m_LocalBuffer);
    m_LocalBuffer = nullptr;
}

Texture::~Texture()
{
    if (m_RendererID)
        GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}