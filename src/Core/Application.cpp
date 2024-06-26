#include "Application.h"

#include "Color.h"
#include "Window.h"
#include "Layer.h"
#include "Time.h"

#include "Event/Event.h"

#include "Renderer/Renderer.h"

using namespace Core;

static Application* s_ApplicationInstance = nullptr;

Application::Application(const char* title)
{
    assert(!s_ApplicationInstance && "Application already exists.");
    s_ApplicationInstance = this;

    const WindowParams params{title, 1200, 800};
    m_Window = std::make_unique<Window>(params);
    m_Window->SetEventCallback(BIND_FN(Application::OnEvent));
    GraphicsContext::LogInfo();

    Renderer::Init();
 
    m_ImguiLayer = new Core::ImguiLayer();
    PushLayer(m_ImguiLayer);
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
    assert(layer);
    m_LayerStack.emplace_back(layer);
    layer->OnAttach();
}

void Application::Start()
{
    while (m_Window->IsOpen())
    {
        double time = Time::GetTime();
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        for (Layer* layer : m_LayerStack)
            layer->OnUpdate(timestep);

        m_ImguiLayer->Begin();
        for (Layer* layer : m_LayerStack)
            layer->OnImgui(timestep);
        m_ImguiLayer->End();

        m_Window->Update();
    }
}

void Application::OnEvent(Event& event)
{
    for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
    {
        if (event.Handled) 
            break;
        (*it)->OnEvent(event);
    }
}
