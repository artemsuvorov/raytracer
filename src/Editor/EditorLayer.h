#pragma once

#include "Core/Layer.h"

namespace Core {

    // Forwards.
    class Shader;

}

namespace Editor {

class EditorLayer final : public Core::Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;

private:
    uint32_t m_VertexBuffer = 0;
    uint32_t m_VertexArray = 0;
    uint32_t m_Texture = 0;
    std::shared_ptr<Core::Shader> m_ScreenShader;
    std::shared_ptr<Core::Shader> m_ComputeShader;
    // uint32_t m_ComputeShader = 0;
};

}
