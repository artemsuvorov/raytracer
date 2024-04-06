#pragma once

namespace Core {
    
// Forwards.
union Color;

// Default graphics renderer class that contains wrapper functions
// around OpenGL specification.
class Renderer final
{
public:
    static void Init();
    static void Shutdown();

    static void Clear(Color color = Color::Black);

    static void DrawTriangle();
};

}