#include "Precompiled.h"
#include "Renderer.h"

#include <GLFW/glfw3.h>

using namespace Core;

void Renderer::Init()
{
}

void Renderer::Shutdown()
{
}

void Renderer::Clear(Color color)
{
    glClearColor(ToRgbaNorm(color.hex));
    glClear(GL_COLOR_BUFFER_BIT);
}
