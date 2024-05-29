#pragma once

#include "Core/Layer.h"

#include "Event/ApplicationEvent.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"

namespace Core {

class ImguiLayer : public Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Timestep dt) override;
    virtual void OnEvent(Event& event) override;

private:
    bool OnWindowResizeEvent(WindowResizeEvent& event);

    bool OnMouseButtonPressed(MouseButtonPressedEvent& event);
    bool OnMouseButtonReleased(MouseButtonReleasedEvent& event);
    bool OnMouseMoved(MouseMovedEvent& event);
    bool OnMouseScrolled(MouseScrolledEvent& event);

    bool OnKeyPressed(KeyPressedEvent& event);
    bool OnKeyReleased(KeyReleasedEvent& event);
    bool OnKeyTyped(KeyTypedEvent& event);
};

}