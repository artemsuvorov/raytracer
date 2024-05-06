#include "Precompiled.h"
#include "Buffer.h"

#include <GL/glew.h>

using namespace Core;

std::shared_ptr<VertexBuffer> VertexBuffer::Create(const float* vertices, uint32_t size)
{
    return std::make_shared<VertexBuffer>(vertices, size);
}

VertexBuffer::VertexBuffer(const float *vertices, uint32_t size)
{
    glCreateBuffers(1, &m_Id);
	glNamedBufferData(m_Id, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t* indices, uint32_t size)
{
    return std::make_shared<IndexBuffer>(indices, size);
}

IndexBuffer::IndexBuffer(const uint32_t* indices, uint32_t size) : m_Size(size)
{
    glCreateBuffers(1, &m_Id);
	glNamedBufferData(m_Id, size * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
