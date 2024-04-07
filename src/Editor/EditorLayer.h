#pragma once

#include "Precompiled.h"
#include "Core/Layer.h"

namespace Editor {

class EditorLayer final : public Core::Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;

private:
    uint32_t m_VertexBuffer = 0;
    uint32_t m_VertexArray = 0;
    uint32_t m_ShaderProgram = 0;
};

}
