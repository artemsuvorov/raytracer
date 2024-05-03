#include "Precompiled.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "EditorLayer.h"

#include <iostream>
#include <array>
#include <GL/glew.h>

using namespace Core;
using namespace Editor;

void EditorLayer::OnAttach()
{
    m_Shader = Shader::Create("res/shader.vert", "res/shader.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f,  0.0f,  // left  
         0.5f, -0.5f,  0.0f,  // right 
         0.0f,  0.5f,  0.0f   // top   
    }; 

    glGenVertexArrays(1, &m_VertexArray);
    glGenBuffers(1, &m_VertexBuffer);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then 
    // configure vertex attributes(s).
    glBindVertexArray(m_VertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as 
    // the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify 
    // this VAO, but this rarely happens. Modifying other VAOs requires a call to 
    // glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when 
    // it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Editor::EditorLayer::OnDetach()
{
    glDeleteVertexArrays(1, &m_VertexArray);
    glDeleteBuffers(1, &m_VertexBuffer);
    // glDeleteProgram(m_ShaderProgram);
}

void EditorLayer::OnUpdate()
{
    Renderer::Clear(0x222222FF);
    
    // draw our first triangle
    m_Shader->Bind();
    // seeing as we only have a single VAO there's no need to bind it every time,
    // but we'll do so to keep things a bit more organized
    glBindVertexArray(m_VertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0); // no need to unbind it every time 
}