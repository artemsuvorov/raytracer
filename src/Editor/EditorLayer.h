#pragma once

#include "Core/Layer.h"
#include "Editor/Scene.h"

namespace Core {

    // Forwards.
    class Window;
    class VertexArray;
    class Shader;
    class Texture;
    class UniformBuffer;

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
    virtual void OnUpdate(Core::Timestep dt) override;
    virtual void OnEvent(Core::Event& event) override;

private:
    bool OnKeyPressed(Core::KeyPressedEvent& event);
    bool OnMouseButtonPressed(Core::MouseButtonPressedEvent& event);

private:
    const Core::Window& m_Window;
    Scene m_Scene;

    glm::vec3 m_CameraPosition {0.0f, 0.0f, 2.0f};

    std::shared_ptr<Core::VertexArray> m_VertexArray;
    std::shared_ptr<Core::UniformBuffer> m_SceneBuffer;

    std::shared_ptr<Core::Shader> m_ScreenShader;
    std::shared_ptr<Core::Shader> m_ComputeShader;

    std::shared_ptr<Core::Texture> m_Texture;
};

}
