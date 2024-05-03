#include "Precompiled.h"
#include "Shader.h"

#include <malloc.h>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

using namespace Core;

std::shared_ptr<Shader> Shader::Create(const std::string& vertexFilepath, const std::string& fragmentFilepath)
{
    return std::make_shared<Shader>(vertexFilepath, fragmentFilepath);
}

Shader::Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
{
    const std::string vertexSource = ReadShader(vertexFilepath);
    const std::string fragmentSource = ReadShader(fragmentFilepath);

    m_Id = CreateProgram(vertexSource, fragmentSource);
}

Shader::~Shader()
{
    glDeleteProgram(m_Id);
}

void Shader::Bind() const
{
	glUseProgram(m_Id);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

std::string Shader::ReadShader(const std::string& filepath)
{
    std::string result;
    
    // ifstream closes itself due to RAII.
    std::ifstream in(filepath, std::ios::in | std::ios::binary);
    if (!in)
    {
        std::cerr << "Shader::ReadShader: Could not open file `" << filepath << "`.\n";
        return result;
    }

    in.seekg(0, std::ios::end);
    const uint32_t size = in.tellg();
    if (size < 0)
    {
        std::cerr << "Shader::ReadShader: Could not read from file `" << filepath << "`.\n";
        return result;
    }

    result.resize(size);
    in.seekg(0, std::ios::beg);
    in.read(&result[0], size);

    return result;
}

static void PrintLinkingErrors(uint32_t program)
{
    int32_t linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked)
        return;

    std::cerr << "Shader::LinkShaders: Shader linking failed for the program " << program << ".\n";
}

uint32_t Shader::CreateProgram(const std::string& vertexSource, const std::string& fragmentSource)
{
    const uint32_t program = glCreateProgram();

    const uint32_t vertexShaderId = CompileShader(GL_VERTEX_SHADER, vertexSource);
    const uint32_t fragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    
    glAttachShader(program, vertexShaderId);
    glAttachShader(program, fragmentShaderId);
    glLinkProgram(program);

    PrintLinkingErrors(program);

    glValidateProgram(program);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return program;
}

static void PrintCompilationErrors(uint32_t type, uint32_t shader)
{
    int32_t compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled)
        return;
    
    int32_t length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(shader, length, &length, message);
    std::cerr << "Shader::CompileShader: Compilation failed:\n" << message << "\n";
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
{
    const uint32_t id = glCreateShader(type);
    const char* sourcePointer = source.c_str();

    glShaderSource(id, 1, &sourcePointer, nullptr);
    glCompileShader(id);

    PrintCompilationErrors(type, id);

    return id;
}
