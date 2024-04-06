#pragma once

#include "Precompiled.h"

namespace Core {

// Forwards.
class Window;
class Layer;

// Application class that setups a window and runs the main loop.
class Application final
{
public:
    Application(const char* title);
    virtual ~Application();

public:
    static Application& Get();

public:
    void PushLayer(Layer* layer);
    void Start();

private:
    std::unique_ptr<Window> m_Window;
    std::vector<Layer*> m_LayerStack;
};

}