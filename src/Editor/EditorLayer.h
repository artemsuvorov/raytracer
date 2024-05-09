#pragma once

#include "Core/Layer.h"

namespace Core {

    // Forwards.
    class Window;
    class VertexArray;
    class Shader;
    class Texture;

    class Event;
    class KeyPressedEvent;
    class MouseButtonPressedEvent;

}

namespace Editor {

class EditorLayer final : public Core::Layer
{
public:
    EditorLayer();

public:
    virtual void OnAttach() override;
    virtual void OnUpdate() override;
    virtual void OnEvent(Core::Event& event) override;

private:
    bool OnKeyPressed(Core::KeyPressedEvent& event);
    bool OnMouseButtonPressed(Core::MouseButtonPressedEvent& event);

private:
    const Core::Window& m_Window;

    glm::vec3 m_CameraPosition = glm::vec3(0.0f);

    std::shared_ptr<Core::VertexArray> m_VertexArray;
    
    std::shared_ptr<Core::Shader> m_ScreenShader;
    std::shared_ptr<Core::Shader> m_ComputeShader;

    std::shared_ptr<Core::Texture> m_Texture;
};

}
