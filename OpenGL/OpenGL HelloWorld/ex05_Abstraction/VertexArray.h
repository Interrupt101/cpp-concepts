#pragma once

#include <glad/glad.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
    unsigned int m_RendererID;

public:
    VertexArray();
    ~VertexArray();

    // Disable copying (VAOs shouldn't be copied)
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    // Allow moving
    VertexArray(VertexArray&& other) noexcept;
    VertexArray& operator=(VertexArray&& other) noexcept;

    void Bind() const;
    void Unbind() const;

    void AddBuffer(const VertexBuffer& vb,
        const VertexBufferLayout& layout);
};