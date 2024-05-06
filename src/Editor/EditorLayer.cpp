#include "Precompiled.h"
#include "EditorLayer.h"

#include "Core/Application.h"
#include "Core/Window.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

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
    const glm::vec2 viewportSize = m_Window.GetSize();
	glCreateTextures(GL_TEXTURE_2D, 1, &m_Texture);
	glTextureParameteri(m_Texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_Texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureStorage2D(m_Texture, 1, GL_RGBA32F, viewportSize.x, viewportSize.y);
	glBindImageTexture(0, m_Texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

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

    glBindTextureUnit(0, m_Texture);

    glBindVertexArray(m_VertexArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}