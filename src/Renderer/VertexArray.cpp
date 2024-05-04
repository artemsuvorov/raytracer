#include "Precompiled.h"
#include "VertexArray.h"

#include <GL/glew.h>

using namespace Core;

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_Id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_Id);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_Id);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
