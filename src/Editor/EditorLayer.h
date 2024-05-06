#pragma once

#include "Core/Layer.h"

namespace Core {

    // Forwards.
    class Window;
    class VertexArray;
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
    virtual void OnUpdate() override;

private:
    const Core::Window& m_Window;

    std::shared_ptr<Core::VertexArray> m_VertexArray;
    
    std::shared_ptr<Core::Shader> m_ScreenShader;
    std::shared_ptr<Core::Shader> m_ComputeShader;

    std::shared_ptr<Core::Texture> m_Texture;
};

}
