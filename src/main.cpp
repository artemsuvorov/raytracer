#include "Core/Application.h"
#include "Editor/EditorLayer.h"

int main(int argc, char** argv)
{
    Core::Application app("Ray Tracing Editor");
    app.PushLayer(new Editor::EditorLayer());
    app.Start();
}