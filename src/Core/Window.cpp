#include "Precompiled.h"
#include "Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace Core;

static uint8_t s_WindowCount = 0u;

Window::Window(const WindowParams& params) : m_Size(params.Width, params.Height)
{
    Init(params);
}

Window::~Window()
{
    Shutdown();
}

bool Window::IsOpen() const
{
    return m_Handle && !glfwWindowShouldClose(m_Handle);
}

void Window::Update()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Handle);
}

void Window::Init(const WindowParams& params)
{
    if (s_WindowCount == 0u)
    {
        const bool initialized = glfwInit();
        assert(initialized && "Failed to initialize GLFW!");
    }

#ifndef NDEBUG
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
    
    m_Handle = glfwCreateWindow(params.Width, params.Height, params.Title, nullptr, nullptr);
    assert(m_Handle && "Failed to initialize GLFW!");
    
    glfwMakeContextCurrent(m_Handle);

	glfwSwapInterval(true);
    glViewport(0, 0, params.Width, params.Height);
    
    const uint32_t status = glewInit();
    assert(status == GLEW_OK && "Failed to initialize GLEW!");
}

void Window::Shutdown()
{
	glfwDestroyWindow(m_Handle);
    glfwTerminate();
}

void GraphicsContext::LogInfo()
{
	std::cout << "OpenGL Info:\n";
	std::cout << "  Vendor: " << glGetString(GL_VENDOR) << "\n";
	std::cout << "  Renderer: " << glGetString(GL_RENDERER) << "\n";
	std::cout << "  Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "GLEW Info:\n";
    std::cout << "  Version: " << glewGetString(GLEW_VERSION) << "\n";
}
