#include "EditorLayer.h"
#include "Core/Core.h"

#include <array>
#include <GL/glew.h>

using namespace Core;
using namespace Editor;

void EditorLayer::OnAttach()
{
    
}

void EditorLayer::OnUpdate()
{
    Renderer::Clear(0x222222FF);

    // Deprecated.
    glBegin(GL_TRIANGLES);
    
    glColor3f(ToRgbNorm(0x2154A6FF));
    glVertex3f(-0.3f, -0.5f, 0.0f);
    glVertex3f( 0.0f,  0.5f, 0.0f);
    glVertex3f( 0.3f, -0.5f, 0.0f);
    
    glEnd();
}