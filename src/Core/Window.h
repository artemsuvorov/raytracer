#pragma once

// Forwards.
struct GLFWwindow;

namespace Core {

// Forwards.
class Event;

struct WindowParams
{
	const char* Title;
	uint32_t Width, Height;
};

// Represents a wrapper class around GLFWwindow handle.
class Window final
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

	Window(const WindowParams& params);
	~Window();

public:
	bool IsOpen() const;
	void Update();

	void SetEventCallback(const EventCallbackFn& callback)
	{
		m_Data.EventCallback = callback;
	}

	glm::vec2 GetSize() const
	{
		return glm::vec2(m_Data.Width, m_Data.Height);
	}

private:
	void Init(const WindowParams& params);
	void Shutdown();

private:
	GLFWwindow* m_Handle = nullptr;
	
	struct WindowData
	{
		std::string Title;
		uint32_t Width, Height;
		EventCallbackFn EventCallback;
	} m_Data;
};

}

namespace Core::GraphicsContext {

// Logs graphics context info.
void LogInfo(); 

}
