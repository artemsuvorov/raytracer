#include "Precompiled.h"
#include "Core.h"

int main(int argc, char** argv)
{
    using namespace Core;

    Window window({"Ray Tracing Editor", 1200u, 800u});
    GraphicsContext::LogInfo();

    while (window.IsOpen())
    {
        Renderer::Clear(0x222222FF);
        window.Update();
    }
}