#include "ImguiLayer.h"
#include "Core/Application.h"
#include "Core/Window.h"

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
    
    static bool show = true;
    ImGui::ShowDemoWindow(&show); 

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiLayer::OnEvent(Event& event)
{
}
