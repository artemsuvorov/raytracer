#include "Precompiled.h"

#include "ImguiLayer.h"
#include "Core/Application.h"
#include "Core/Window.h"
#include "Event/Event.h"

#include "imgui/imgui.h"
#include "UI/ImguiRenderer.h"

using namespace Core;

void ImguiLayer::OnAttach()
{
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    // Enable Multi-Viewport / Platform Windows

    static constexpr const float kFontSize = 18.0f;
    io.Fonts->AddFontFromFileTTF("res/fonts/Roboto-Medium.ttf", kFontSize);

    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImguiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void ImguiLayer::OnUpdate(Timestep dt)
{
    const glm::vec2 size = Application::Get().GetWindow().GetSize();
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(size.x, size.y);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    if (ImGui::Begin("Debug"))
    {
        ImGui::Text("FPS: %0.3f", 1.0f / (float)dt);
        ImGui::Text("Delta Time: %0.3f", (float)dt);
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiLayer::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(OnWindowResizeEvent));

    dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_FN(OnMouseButtonPressed));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_FN(OnMouseButtonReleased));
    dispatcher.Dispatch<MouseMovedEvent>(BIND_FN(OnMouseMoved));
    dispatcher.Dispatch<MouseScrolledEvent>(BIND_FN(OnMouseScrolled));

    dispatcher.Dispatch<KeyPressedEvent>(BIND_FN(OnKeyPressed));
    dispatcher.Dispatch<KeyReleasedEvent>(BIND_FN(OnKeyReleased));
    dispatcher.Dispatch<KeyTypedEvent>(BIND_FN(OnKeyTyped));
}

bool ImguiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    return false;
}

bool ImguiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[event.GetMouseButton()] = true;
    return false;
}

bool ImguiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[event.GetMouseButton()] = false;
    return false;
}

bool ImguiLayer::OnMouseMoved(MouseMovedEvent& event)
{
    
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(event.GetX(), event.GetY());
    return false;
}

bool ImguiLayer::OnMouseScrolled(MouseScrolledEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += event.GetXOffset();
    io.MouseWheel  += event.GetYOffset();
    return false;
}

bool ImguiLayer::OnKeyPressed(KeyPressedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[event.GetKeyCode()] = true;
    // TODO: Set for modifiers pressed (Shift, Ctrl, Alt, etc.)
    return false;
}

bool ImguiLayer::OnKeyReleased(KeyReleasedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[event.GetKeyCode()] = false;
    // TODO: Set for modifiers pressed (Shift, Ctrl, Alt, etc.)
    return false;
}

bool ImguiLayer::OnKeyTyped(KeyTypedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    const uint32_t keycode = event.GetKeyCode();
    if (keycode < 0x10000)
        io.AddInputCharacter(keycode);
    return false;
}
