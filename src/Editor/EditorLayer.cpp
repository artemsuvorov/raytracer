#include "Precompiled.h"
#include "EditorLayer.h"

#include "Core/Application.h"
#include "Core/Window.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include <iostream>
#include <array>
#include <math.h>
#include <GL/glew.h>

using namespace Core;
using namespace Editor;

Editor::EditorLayer::EditorLayer() : m_Window(Application::Get().GetWindow())
{
}

void EditorLayer::OnAttach()
{
    const float vertices[] =
    {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };

    const uint32_t indices[] =
    {
        0, 2, 1,
        0, 3, 2,
    };

    uint32_t EBO;
	glCreateVertexArrays(1, &m_VertexArray);
	glCreateBuffers(1, &m_VertexBuffer);
	glCreateBuffers(1, &EBO);

	glNamedBufferData(m_VertexBuffer, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glNamedBufferData(EBO, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(m_VertexArray, 0);
	glVertexArrayAttribBinding(m_VertexArray, 0, 0);
	glVertexArrayAttribFormat(m_VertexArray, 0, 3, GL_FLOAT, GL_FALSE, 0);

	glEnableVertexArrayAttrib(m_VertexArray, 1);
	glVertexArrayAttribBinding(m_VertexArray, 1, 0);
	glVertexArrayAttribFormat(m_VertexArray, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));

	glVertexArrayVertexBuffer(m_VertexArray, 0, m_VertexBuffer, 0, 5 * sizeof(GLfloat));
	glVertexArrayElementBuffer(m_VertexArray, EBO);

    // Texture.
    m_Texture = Texture::Create()
        .WithSize(m_Window.GetSize().x, m_Window.GetSize().y)
        .WithFormat(ImageFormat::kRgba32f)
        .WithFilter(ImageFilter::kNearest)
        .WithWrapping(TextureWrap::kClampToEdge)
        .Build();
    m_Texture->BindWriteLevel();

    m_ScreenShader = Shader::Create()
        .Attach(ShaderType::kVertexShader, "res/shader.vert")
        .Attach(ShaderType::kFragmentShader, "res/shader.frag")
        .Link();

    m_ComputeShader = Shader::Create()
        .Attach(ShaderType::kComputeShader, "res/tracing.comp")
        .Link();
}

void EditorLayer::OnDetach()
{
    glDeleteVertexArrays(1, &m_VertexArray);
    glDeleteBuffers(1, &m_VertexBuffer);
}

void EditorLayer::OnUpdate()
{
    Renderer::Clear(0x222222FF);
    
    m_ComputeShader->Bind();
    const glm::vec2 viewportSize = m_Window.GetSize();
    glDispatchCompute(ceil(viewportSize.x / 8), ceil(viewportSize.y / 4), 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    m_ScreenShader->Bind();
    m_ScreenShader->SetUniform("screen", 0);

    m_Texture->Bind(0);    

    glBindVertexArray(m_VertexArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}