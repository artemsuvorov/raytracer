#pragma once

#include "Precompiled.h"
#include "Core/Layer.h"

namespace Editor {

class EditorLayer final : public Core::Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnUpdate() override;

private:
    uint32_t m_BaseClearColor = 0x000000FFu;
    uint32_t m_BlueColorDelta = 0u;
};

}
