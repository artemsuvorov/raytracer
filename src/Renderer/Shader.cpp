#include "Precompiled.h"
#include "Shader.h"

#include <malloc.h>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

using namespace Core;

ShaderBuilder Shader::Create()
{
    return ShaderBuilder();
}

Shader::Shader(uint32_t id) : m_Id(id)
{
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

void Shader::SetUniform(const std::string& name, uint32_t value)
{
    const int32_t location = FindUniform(name);
    glUniform1i(location, value);
}

void Shader::SetUniform(const std::string& name, float value)
{
    const int32_t location = FindUniform(name);
    glUniform1f(location, value);
}

void Shader::SetUniform(const std::string& name, const glm::vec2& value)
{
    const int32_t location = FindUniform(name);
    glUniform2f(location, value.x, value.y);
}

void Shader::SetUniform(const std::string& name, const glm::vec3& value)
{
    const int32_t location = FindUniform(name);
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetUniform(const std::string& name, const glm::vec4& value)
{
    const int32_t location = FindUniform(name);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetUniform(const std::string& name, const glm::mat4& value)
{
    const int32_t location = FindUniform(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

int32_t Shader::FindUniform(const std::string& name)
{
    const int32_t location = glGetUniformLocation(m_Id, name.c_str());
    //if (location < 0)
    //    std::cerr << "Could not find uniform '" << name << "' in Shader " << m_Id << ".\n";
    return location;
}

static uint32_t ShaderTypeToEnum(ShaderType type)
{
    switch (type)
    {
        default:
            assert(false && "Unexpected shader type.");
            return 0;

        case ShaderType::kVertexShader:     return GL_VERTEX_SHADER;
        case ShaderType::kFragmentShader:   return GL_FRAGMENT_SHADER;
        case ShaderType::kComputeShader:    return GL_COMPUTE_SHADER;
    }
}

static void PrintCompilationErrors(uint32_t shader)
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

static void PrintLinkingErrors(uint32_t program)
{
    int32_t linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked)
        return;

    std::cerr << "Shader::LinkShaders: Shader linking failed for the program " << program << ".\n";
}

ShaderBuilder::ShaderBuilder()
{
    m_ProgramId = glCreateProgram();
}

ShaderBuilder& ShaderBuilder::Attach(ShaderType type, const std::string& filepath)
{
    const std::string source = ReadShader(filepath);
    const uint32_t shader = CompileShader(type, source);

    glAttachShader(m_ProgramId, shader);
    m_AttachedShaders.push_back(shader);

    return *this;
}

std::shared_ptr<Shader> ShaderBuilder::Link()
{
    glLinkProgram(m_ProgramId);
    PrintLinkingErrors(m_ProgramId);
    glValidateProgram(m_ProgramId);

    for (const uint32_t shader : m_AttachedShaders)
        glDeleteShader(shader);

    return std::make_shared<Shader>(m_ProgramId);
}

std::string ShaderBuilder::ReadShader(const std::string& filepath)
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

uint32_t ShaderBuilder::CompileShader(ShaderType type, const std::string& source)
{
    const uint32_t id = glCreateShader(ShaderTypeToEnum(type));
    const char* sourcePointer = source.c_str();

    glShaderSource(id, 1, &sourcePointer, nullptr);
    glCompileShader(id);

    PrintCompilationErrors(id);

    return id;
}
