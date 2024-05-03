#pragma once

#include "Core/Color.h"

namespace Core {

// Default graphics renderer class that contains wrapper functions
// around OpenGL specification.
class Renderer final
{
public:
    static void Init();
    static void Shutdown();

    static void Clear(Color color = Color::Black);
};

}