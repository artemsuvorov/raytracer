#include "Precompiled.h"
#include "Buffer.h"

#include <GL/glew.h>

using namespace Core;

std::shared_ptr<VertexBuffer> Core::VertexBuffer::Create(std::initializer_list<float> vertices)
{
    return Create(vertices.begin(), vertices.size() * sizeof(vertices.begin()));
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(const float* vertices, uint32_t size)
{
    return std::make_shared<VertexBuffer>(vertices, size);
}

VertexBuffer::VertexBuffer(const float* vertices, uint32_t size)
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

std::shared_ptr<IndexBuffer> Core::IndexBuffer::Create(std::initializer_list<uint32_t> indices)
{
    return Create(indices.begin(), indices.size() * sizeof(indices.begin()));
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t *indices, uint32_t size)
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

std::shared_ptr<UniformBuffer> UniformBuffer::Create(const void* data, uint32_t size)
{
    return std::make_shared<UniformBuffer>(data, size);
}

UniformBuffer::UniformBuffer(const void* data, uint32_t size)
{
    glGenBuffers(1, &m_Id);
    glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
    glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::~UniformBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

void UniformBuffer::SetBinding(uint32_t bindingIndex) const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, m_Id);
}

void UniformBuffer::SetData(const void* data, uint32_t size) const
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_Id);
    glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
