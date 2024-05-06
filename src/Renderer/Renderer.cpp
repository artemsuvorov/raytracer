#include "Precompiled.h"
#include "Renderer.h"

#include "Buffer.h"
#include "VertexArray.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Core;

void Renderer::Init()
{
}

void Renderer::Shutdown()
{
}

void Core::Renderer::DispatchCompute(uint32_t width, uint32_t height)
{
    glDispatchCompute(width, height, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

void Renderer::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t indexCount)
{
    vertexArray->Bind();
    const uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear(Color color)
{
    glClearColor(ToRgbaNorm(color.hex));
    glClear(GL_COLOR_BUFFER_BIT);
}
