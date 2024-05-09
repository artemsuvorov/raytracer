#pragma once

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
    // TODO: Add DeltaTime parameter.
    virtual void OnUpdate() {}
    virtual void OnEvent(Event& event) {}
};

}