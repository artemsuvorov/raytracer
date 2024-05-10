#include "Time.h"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

using namespace Core;

double Time::GetTime()
{
    return glfwGetTime();
}
