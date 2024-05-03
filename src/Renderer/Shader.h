#pragma once

namespace Core {

    // OpenGL Shader.
    class Shader final
    {
    public:
        // Preferred way to instantiate Shaders.
        static std::shared_ptr<Shader> Create(const std::string& vertexFilepath, const std::string& fragmentFilepath);

        Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
        ~Shader();

        void Bind() const;
		void Unbind() const;

    private:
        std::string ReadShader(const std::string& filepath);
        uint32_t CreateProgram(const std::string& vertexSource, const std::string& fragmentSource);
        uint32_t CompileShader(uint32_t type, const std::string& source);

	private:
		uint32_t m_Id;
    };

}