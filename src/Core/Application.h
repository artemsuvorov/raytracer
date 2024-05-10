#pragma once

#include "Precompiled.h"

namespace Core {

// Forwards.
class Window;
class Layer;
class Event;

// Application class that setups a window and runs the main loop.
class Application final
{
public:
    Application(const char* title);
    virtual ~Application();

public:
    static Application& Get();

    void PushLayer(Layer* layer);
    void Start();

    void OnEvent(Event& event);

    const Window& GetWindow() const { return *m_Window; }

private:
    std::unique_ptr<Window> m_Window;
    std::vector<Layer*> m_LayerStack;

    double m_LastFrameTime = 0.0;
};

}