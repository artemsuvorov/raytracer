#include "Precompiled.h"
#include "Core/Core.h"
#include "EditorLayer.h"

#include <iostream>
#include <array>
#include <GL/glew.h>

using namespace Core;
using namespace Editor;

static constexpr const char* GVertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

static constexpr const char* GFragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void EditorLayer::OnAttach()
{
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &GVertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int32_t success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << "\n";
    }
    // fragment shader
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &GFragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    m_ShaderProgram = glCreateProgram();
    glAttachShader(m_ShaderProgram, vertexShader);
    glAttachShader(m_ShaderProgram, fragmentShader);
    glLinkProgram(m_ShaderProgram);
    // check for linking errors
    glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f,  0.0f,  // left  
         0.5f, -0.5f,  0.0f,  // right 
         0.0f,  0.5f,  0.0f   // top   
    }; 

    glGenVertexArrays(1, &m_VertexArray);
    glGenBuffers(1, &m_VertexBuffer);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then 
    // configure vertex attributes(s).
    glBindVertexArray(m_VertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as 
    // the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify 
    // this VAO, but this rarely happens. Modifying other VAOs requires a call to 
    // glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when 
    // it's not directly necessary.
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Editor::EditorLayer::OnDetach()
{
    glDeleteVertexArrays(1, &m_VertexArray);
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteProgram(m_ShaderProgram);
}

void EditorLayer::OnUpdate()
{
    Renderer::Clear(0x222222FF);
    
    // draw our first triangle
    glUseProgram(m_ShaderProgram);
    // seeing as we only have a single VAO there's no need to bind it every time,
    // but we'll do so to keep things a bit more organized
    glBindVertexArray(m_VertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0); // no need to unbind it every time 
}