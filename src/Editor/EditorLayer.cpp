#include "Precompiled.h"
#include "EditorLayer.h"

#include "Core/Application.h"
#include "Core/Window.h"

#include "Renderer/Renderer.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
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
        // XYZ Position      // UV
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
         1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
    };

    const uint32_t indices[] = { 0, 2, 1, 0, 3, 2, };

    const auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    const auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices));
    const BufferLayout layout = {
		{ ShaderDataType::Float3, "pos" },
		{ ShaderDataType::Float2, "uvs" },
	};
    m_VertexArray = VertexArray::Create(layout, vertexBuffer, indexBuffer);

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

void EditorLayer::OnUpdate()
{
    Renderer::Clear(0x222222FF);
    
    m_ComputeShader->Bind();
    glDispatchCompute(ceil(m_Window.GetSize().x / 8), ceil(m_Window.GetSize().y / 4), 1);
    // glMemoryBarrier(GL_ALL_BARRIER_BITS);

    m_ScreenShader->Bind();
    m_ScreenShader->SetUniform("screen", 0);

    m_Texture->Bind(0);    

    m_VertexArray->Bind();
    const uint32_t count = m_VertexArray->GetIndexBuffer()->GetCount();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}