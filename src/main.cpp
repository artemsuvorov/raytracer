#include "Core/Application.h"
#include "Editor/EditorLayer.h"
#include "UI/ImguiLayer.h"

int main(int argc, char** argv)
{
    Core::Application app("Ray Tracing Editor");
    app.PushLayer(new Editor::EditorLayer());
    app.PushLayer(new Core::ImguiLayer());
    app.Start();
}