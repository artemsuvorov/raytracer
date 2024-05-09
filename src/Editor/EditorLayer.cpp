#include "Precompiled.h"
#include "EditorLayer.h"

#include "Core/Application.h"
#include "Core/Window.h"

#include "Renderer/Renderer.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include <math.h>
#include <iostream>
#include <GLFW/glfw3.h>

using namespace Core;
using namespace Editor;

EditorLayer::EditorLayer() : m_Window(Application::Get().GetWindow())
{
}

void EditorLayer::OnAttach()
{
    const auto vertexBuffer = VertexBuffer::Create({
        // XYZ Position      // UV
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
         1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
    });
    const auto indexBuffer = IndexBuffer::Create({ 0, 2, 1, 0, 3, 2, });
    const BufferLayout layout = {
		{ ShaderDataType::Float3, "pos" },
		{ ShaderDataType::Float2, "uvs" },
	};
    m_VertexArray = VertexArray::Create(layout, vertexBuffer, indexBuffer);

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
    m_ComputeShader->SetUniform("u_Camera", m_CameraPosition);
    Renderer::DispatchCompute(ceil(m_Window.GetSize().x / 8), ceil(m_Window.GetSize().y / 4));

    m_ScreenShader->Bind();
    m_ScreenShader->SetUniform("screen", 0u);

    m_Texture->Bind(0);    

    Renderer::DrawIndexed(m_VertexArray);
}

void EditorLayer::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<KeyPressedEvent>(BIND_FN(EditorLayer::OnKeyPressed));
    dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_FN(EditorLayer::OnMouseButtonPressed));
}

bool EditorLayer::OnKeyPressed(KeyPressedEvent& event)
{
    glm::vec3 direction = glm::vec3(0.0f);

    const KeyCode keycode = event.GetKeyCode();
    direction.z = (keycode == Key::W) - (keycode == Key::S);
    direction.x = (keycode == Key::D) - (keycode == Key::A);
    direction.y = (keycode == Key::Space) - (keycode == Key::LeftShift);

    if (glm::dot(direction, direction) > 0e-25f)
        direction = glm::normalize(direction);

    constexpr static const float kSpeed = 0.05f;
    m_CameraPosition += kSpeed * direction;

    return false;
}

bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& event)
{
    return false;
}
