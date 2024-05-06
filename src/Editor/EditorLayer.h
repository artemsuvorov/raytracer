#pragma once

#include "Core/Layer.h"
#include <glm/vec2.hpp>

namespace Core {

    // Forwards.
    class Window;
    class Shader;
    class Texture;

}

namespace Editor {

class EditorLayer final : public Core::Layer
{
public:
    EditorLayer();

public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;

private:
    const Core::Window& m_Window;
    
    std::shared_ptr<Core::Shader> m_ScreenShader;
    std::shared_ptr<Core::Shader> m_ComputeShader;

    std::shared_ptr<Core::Texture> m_Texture = 0;

    uint32_t m_VertexBuffer = 0;
    uint32_t m_VertexArray = 0;
};

}
