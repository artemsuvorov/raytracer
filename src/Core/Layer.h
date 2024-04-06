#pragma once

#include "Precompiled.h"

namespace Core {

// Empty Layer base class.
class Layer
{
public:
    Layer() = default;
    virtual ~Layer() = default;

public:
    virtual void OnAttach() {}
    virtual void OnDetach() {}
    // TODO: Add DeltaTime parameter.
    virtual void OnUpdate() {}
};

}