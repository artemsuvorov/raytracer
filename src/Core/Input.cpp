#include "Precompiled.h"
#include "Window.h"
#include "Application.h"
#include "Input.h"

#include <GLFW/glfw3.h>

using namespace Core;

bool Input::IsKeyPressed(const KeyCode key)
{
    GLFWwindow* window = Application::Get().GetWindow().GetHandle();
    int32_t state = glfwGetKey(window, static_cast<int32_t>(key));
    return state == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(const MouseCode button)
{
    GLFWwindow* window = Application::Get().GetWindow().GetHandle();
    auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
    return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition()
{
    GLFWwindow* window = Application::Get().GetWindow().GetHandle();
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return { (float)x, (float)y };
}

float Input::GetMouseX()
{
    return GetMousePosition().x;
}

float Input::GetMouseY()
{
    return GetMousePosition().y;
}
