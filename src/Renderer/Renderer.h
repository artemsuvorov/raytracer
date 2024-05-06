#pragma once

#include "Core/Color.h"

namespace Core {

// Forwards.
class VertexArray;

// Default graphics renderer class that contains wrapper functions
// around OpenGL specification.
class Renderer final
{
public:
    static void Init();
    static void Shutdown();

    static void DispatchCompute(uint32_t width, uint32_t height);
    static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0);

    static void Clear(Color color = Color::Black);
};

}