#pragma once

#include "Time.h"

namespace Core {

// Forwards.
class Event;

// Empty Layer base class.
class Layer
{
public:
    Layer() = default;
    virtual ~Layer() = default;

public:
    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate(Timestep dt) {}
    virtual void OnImgui(Timestep dt) {}
    virtual void OnEvent(Event& event) {}
};

}