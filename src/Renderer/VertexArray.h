#pragma once

namespace Core {

    class VertexArray final
    {
    public:
        VertexArray();
		~VertexArray();
    
        void Bind() const;
        void Unbind() const;

    private:
        uint32_t m_Id;
    };

}