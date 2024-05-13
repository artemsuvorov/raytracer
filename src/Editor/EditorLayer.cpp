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
    Sphere sphere;
    sphere.Position = glm::vec3(0.0f, -0.5f, -1.0f);
    sphere.Radius = 0.5f;
    sphere.Material.Albedo = glm::vec3(0.0f, 0.0f, 1.0f);
    sphere.Material.Roughness = 0.2f;
    m_Scene.Spheres.push_back(sphere);

    Sphere leftWall;
    leftWall.Position = glm::vec3(-101.5f, 0.0f, -1.0f);
    leftWall.Radius = 100.0f;
    leftWall.Material.Albedo = glm::vec3(1.0f, 0.0f, 0.0f);
    leftWall.Material.Roughness = 1.0f;
    m_Scene.Spheres.push_back(leftWall);

    Sphere rightWall;
    rightWall.Position = glm::vec3(101.5f, 0.0f, -1.0f);
    rightWall.Radius = 100.0f;
    rightWall.Material.Albedo = glm::vec3(0.0f, 1.0f, 0.0f);
    rightWall.Material.Roughness = 1.0f;
    m_Scene.Spheres.push_back(rightWall);

    Sphere backWall;
    backWall.Position = glm::vec3(0.0f, 0.0f, -102.5f);
    backWall.Radius = 100.0f;
    backWall.Material.Albedo = glm::vec3(1.0f, 1.0f, 1.0f);
    backWall.Material.Roughness = 1.0f;
    m_Scene.Spheres.push_back(backWall);

    // Sphere ceiling;
    // ceiling.Position = glm::vec3(0.0f, 101.0f, -1.0f);
    // ceiling.Radius = 100.0f;
    // ceiling.Material.Albedo = glm::vec3(1.0f, 1.0f, 1.0f);
    // ceiling.Material.Roughness = 1.0f;
    // m_Scene.Spheres.push_back(ceiling);

    Sphere floor;
    floor.Position = glm::vec3(0.0f, -101.0f, -1.0f);
    floor.Radius = 100.0f;
    floor.Material.Albedo = glm::vec3(1.0f, 1.0f, 1.0f);
    floor.Material.Roughness = 1.0f;
    m_Scene.Spheres.push_back(floor);

    Sphere light;
    light.Position = glm::vec3(0.0f, 0.7f, 0.8f);
    light.Radius = 0.2f;
    light.Material.Albedo = glm::vec3(0.8f, 0.7f, 0.2f);
    light.Material.Roughness = 1.0f;
    light.Material.Emission = 3.0f;
    m_Scene.Spheres.push_back(light);
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

    // if (false) // For debugging purposes only.
    //     std::cout << 1.0f / dt << std::endl;

    m_ComputeShader->Bind();
    m_ComputeShader->SetUniform("u_FrameIndex", glm::vec2(++m_FrameIndex, 0.0f));
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
