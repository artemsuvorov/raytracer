#include "Precompiled.h"
#include "Window.h"

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace Core;

static uint8_t s_WindowCount = 0u;

Window::Window(const WindowParams& params)
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
    m_Data.Title = params.Title;
    m_Data.Width = params.Width;
    m_Data.Height = params.Height;

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

	glfwSwapInterval(false);
    glViewport(0, 0, params.Width, params.Height);
	
    glfwSetWindowUserPointer(m_Handle, &m_Data);
    
    // Set GLFW callbacks.
    glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;
        WindowResizeEvent event(width, height);
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });
    
    glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, true);
                data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetCharCallback(m_Handle, [](GLFWwindow* window, unsigned int keycode)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        KeyTypedEvent event(keycode);
        data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action)
        {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xOffset, double yOffset)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xPos, double yPos)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event);
    });

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
