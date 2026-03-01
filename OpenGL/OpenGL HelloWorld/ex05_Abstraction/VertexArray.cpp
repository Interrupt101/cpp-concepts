#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

// Move constructor
VertexArray::VertexArray(VertexArray&& other) noexcept
    : m_RendererID(other.m_RendererID)
{
    other.m_RendererID = 0;
}

// Move assignment
VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
{
    if (this != &other)
    {
        glDeleteVertexArrays(1, &m_RendererID);

        m_RendererID = other.m_RendererID;
        other.m_RendererID = 0;
    }
    return *this;
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb,
    const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();

    const auto& elements = layout.GetElements();
    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];

        GLCall(glEnableVertexAttribArray(i));

        GLCall(glVertexAttribPointer(
            i,
            element.count,
            element.type,
            element.normalized,
            layout.GetStride(),
            (const void*)(uintptr_t)offset
        ));

        offset += element.count *
            VertexBufferElement::GetSizeOfType(element.type);
    }
}