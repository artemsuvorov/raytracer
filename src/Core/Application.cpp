#include "Application.h"
#include "Core.h"

using namespace Core;

static Application* s_ApplicationInstance = nullptr;

Application::Application(const char* title)
{
    assert(!s_ApplicationInstance && "Application already exists.");
    s_ApplicationInstance = this;

    const WindowParams params{title, 1200u, 800u};
    m_Window = std::make_unique<Window>(params);
    GraphicsContext::LogInfo();

    Renderer::Init();
}

Application::~Application()
{
    for (Layer* layer : m_LayerStack)
    {
        layer->OnDetach();
        delete layer;
    }

    Renderer::Shutdown();
}

Application& Application::Get()
{
    return *s_ApplicationInstance;
}

void Application::PushLayer(Layer* layer)
{
    m_LayerStack.emplace_back(layer);
}

void Application::Start()
{
    while (m_Window->IsOpen())
    {
        Renderer::Clear(0x222222FF);

        for (Layer* layer : m_LayerStack)
            layer->OnUpdate();

        m_Window->Update();
    }
}
