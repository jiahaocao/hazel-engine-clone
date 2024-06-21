#include "hzpch.h"
#include "GLFW2Hazel.h"

#include <GLFW/glfw3.h>

#include "WindowsWindow.h"

#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/WindowEvent.h"

namespace Hazel {

GLFWData::GLFWData(GLFWwindow *window) : m_Window(window), m_Time(0.0)
{
    InstallCallbacks();
}

GLFWData::~GLFWData() { }


void GLFWData::InstallCallbacks()
{
    m_CallbackWindowSize = glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height)
        {
            // Access user data through user pointer.
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            // Synchronize window states.
            data.width = width;
            data.height = height;

            // Create and fire a Hazel event.
            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

    m_CallbackWindowClose = glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);
        });

    m_CallbackCursorPos = glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double x, double y)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)x, (float)y);
            data.eventCallback(event);
        });

    m_CallbackMouseButton = glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            switch (action) {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.eventCallback(event);
                break;
            }
            }
        });

    m_CallbackScroll = glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xoffset, double yoffset)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.eventCallback(event);
        });

    m_CallbackKey = glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            switch (action) {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                data.eventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, 1);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                data.eventCallback(event);
                break;
            }
            }
        });
}

}  // namespace Hazel
