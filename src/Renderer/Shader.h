#pragma once

namespace Core {

// Forwards.
class ShaderBuilder;

// OpenGL Shader.
class Shader final
{
public:
    static ShaderBuilder Create();

    Shader(uint32_t id);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform(const std::string& name, int32_t value);
    void SetUniform(const std::string& name, float value);

private:
    uint32_t m_Id;
};

enum class ShaderType
{
    kNone,
    kVertexShader,
    kFragmentShader,
    kComputeShader,
};

class ShaderBuilder final
{
public:
    ShaderBuilder();

    ShaderBuilder& Attach(ShaderType type, const std::string& filepath);
    std::shared_ptr<Shader> Link();

private:
    std::string ReadShader(const std::string& filepath);
    uint32_t CompileShader(ShaderType type, const std::string& source);

private:
    uint32_t m_ProgramId;
    std::vector<uint32_t> m_AttachedShaders;
};

}