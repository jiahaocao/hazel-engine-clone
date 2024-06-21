#include "hzpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "Hazel/Application.h"

namespace Hazel {

InputManager *InputManager::s_Instance = new WindowsInputManager();

bool WindowsInputManager::IsKeyPressedImpl(int keyCode)
{
    GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    int state = glfwGetKey(window, keyCode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInputManager::IsMouseButtonPressedImpl(int button)
{
    GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    int state = glfwGetMouseButton(window, button);
    return state;
}

std::pair<float, float> WindowsInputManager::GetMousePositionImpl()
{
    GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    double xpos = 0.0, ypos = 0.0;
    glfwGetCursorPos(window, &xpos, &ypos);
    return { (float)xpos, (float)ypos };
}

float WindowsInputManager::GetMouseXImpl()
{
    auto [xpos, ypos] = GetMousePosition();
    return xpos;
}

float WindowsInputManager::GetMouseYImpl()
{
    auto [xpos, ypos] = GetMousePosition();
    return ypos;
}

}  // namespace Hazel
