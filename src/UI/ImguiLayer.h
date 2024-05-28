#pragma once

#include "Core/Layer.h"

namespace Core {

class ImguiLayer : public Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Timestep dt) override;
    virtual void OnEvent(Event& event) override;
};

}