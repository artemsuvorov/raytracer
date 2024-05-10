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
#include <GL/glew.h>

using namespace Core;
using namespace Editor;

EditorLayer::EditorLayer() : m_Window(Application::Get().GetWindow())
{
    Sphere sphere1;
    sphere1.Position = glm::vec3(0.5f, -0.5f, 0.0f);
    sphere1.Radius = 0.5f;
    sphere1.Albedo = glm::vec3(1.0f, 0.0f, 0.0f);
    m_Scene.Spheres.push_back(sphere1);

    Sphere sphere2;
    sphere2.Position = glm::vec3(-2.0f, 0.0f, -3.0f);
    sphere2.Radius = 2.0f;
    sphere2.Albedo = glm::vec3(0.0f, 0.0f, 1.0f);
    m_Scene.Spheres.push_back(sphere2);

    Sphere sphere3;
    sphere3.Position = glm::vec3(1.5f, 1.0f, -2.0f);
    sphere3.Radius = 1.0f;
    sphere3.Albedo = glm::vec3(0.0f, 1.0f, 0.0f);
    m_Scene.Spheres.push_back(sphere3);
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

    m_SceneBuffer = UniformBuffer::Create(&m_Scene.Spheres.front(), sizeof(Sphere) * m_Scene.Spheres.size());
    m_SceneBuffer->SetBinding(1);
}

void EditorLayer::OnUpdate(Timestep dt)
{
    UpdateCamera(dt);
    Renderer::Clear(0x222222FF);

#ifndef NDEBUG // For debugging purposes only.
    std::cout << 1.0f / dt << std::endl;
#endif

    m_ComputeShader->Bind();
    m_ComputeShader->SetUniform("u_CameraPosition", m_CameraPosition);
    Renderer::DispatchCompute(ceil(m_Window.GetSize().x / 8), ceil(m_Window.GetSize().y / 4));

    m_ScreenShader->Bind();
    m_ScreenShader->SetUniform("screen", 0u);

    m_Texture->Bind(0);

    Renderer::DrawIndexed(m_VertexArray);
}

void EditorLayer::UpdateCamera(Timestep dt)
{
    glm::vec3 direction = glm::vec3(0.0f);

    direction.z = (Input::IsKeyPressed(Key::W)) - (Input::IsKeyPressed(Key::S));
    direction.x = (Input::IsKeyPressed(Key::A)) - (Input::IsKeyPressed(Key::D));
    direction.y = (Input::IsKeyPressed(Key::LeftShift)) - (Input::IsKeyPressed(Key::Space));

    if (glm::dot(direction, direction) > 0e-25f)
        direction = -1.0f * glm::normalize(direction);

    constexpr static const float kSpeed = 4.0f;
    m_CameraPosition += dt * kSpeed * direction;
}
