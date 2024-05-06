#pragma once

namespace Core {

// Forwards.
class BufferLayout;
class VertexBuffer;
class IndexBuffer;

class VertexArray final
{
public:
    static std::shared_ptr<VertexArray> Create(
        const BufferLayout& layout,
        std::shared_ptr<VertexBuffer> vertexBuffer,
        std::shared_ptr<IndexBuffer> indexBuffer);

    VertexArray(
        const BufferLayout& layout,
        std::shared_ptr<VertexBuffer> vertexBuffer,
        std::shared_ptr<IndexBuffer> indexBuffer);

    ~VertexArray();

public:
    void Bind() const;
    void Unbind() const;

    std::shared_ptr<VertexBuffer> GetVertexBuffer() { return m_VertexBuffer; }
    std::shared_ptr<IndexBuffer> GetIndexBuffer() { return m_IndexBuffer; }

private:
    void SetLayout(const BufferLayout& layout);
    void SetVertexBuffer(const BufferLayout& layout, std::shared_ptr<VertexBuffer> vertexBuffer);
    void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);

private:
    uint32_t m_Id = 0;

    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

}