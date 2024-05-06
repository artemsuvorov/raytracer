#include "Precompiled.h"
#include "VertexArray.h"
#include "Buffer.h"

#include <GL/glew.h>

using namespace Core;

std::shared_ptr<VertexArray> VertexArray::Create(
    const BufferLayout& layout,
    std::shared_ptr<VertexBuffer> vertexBuffer,
    std::shared_ptr<IndexBuffer> indexBuffer)
{
    return std::make_shared<VertexArray>(layout, vertexBuffer, indexBuffer);
}

VertexArray::VertexArray(
    const BufferLayout& layout,
    std::shared_ptr<VertexBuffer> vertexBuffer,
    std::shared_ptr<IndexBuffer> indexBuffer)
    : m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer)
{
    glCreateVertexArrays(1, &m_Id);

    SetLayout(layout);
    SetVertexBuffer(layout, vertexBuffer);
    SetIndexBuffer(indexBuffer);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_Id);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_Id);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void Core::VertexArray::SetLayout(const BufferLayout& layout)
{
    uint32_t attributeIndex = 0;

    for (const BufferElement& attribute : layout)
    {
        const uint32_t count = attribute.GetComponentCount();
        const uint32_t offset = attribute.Offset;

        glEnableVertexArrayAttrib(m_Id, attributeIndex);
        glVertexArrayAttribBinding(m_Id, attributeIndex, 0);
        glVertexArrayAttribFormat(m_Id, attributeIndex, count, GL_FLOAT, GL_FALSE, offset);
    
        attributeIndex++;
    }
}

void VertexArray::SetVertexBuffer(const BufferLayout& layout, std::shared_ptr<VertexBuffer> vertexBuffer)
{
	glVertexArrayVertexBuffer(m_Id, 0, vertexBuffer->m_Id, 0, layout.GetStride());
}

void VertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer)
{
	glVertexArrayElementBuffer(m_Id, indexBuffer->m_Id);
}
