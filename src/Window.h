#pragma once

// Forwards.
struct GLFWwindow;

namespace Core {

struct WindowParams
{
	const char* Title;
	uint32_t Width;
	uint32_t Height;
};

// Represents a wrapper class around GLFWwindow handle.
class Window final
{
public:
	Window(const WindowParams& params);
	~Window();

public:
	bool IsOpen() const;
	void Update();

private:
	void Init(const WindowParams& params);
	void Shutdown();

private:
	GLFWwindow* m_Handle = nullptr;
};

}

namespace Core::GraphicsContext {

// Logs graphics context info.
void LogInfo(); 

}
