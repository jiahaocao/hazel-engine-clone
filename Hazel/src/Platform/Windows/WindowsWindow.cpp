#include "hzpch.h"
#include "WindowsWindow.h"

#include <glad/glad.h>

#include "Hazel/Log.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/WindowEvent.h"
#include "Hazel/Events/AppEvent.h"

namespace Hazel {

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int err, const char *msg)
{
    HZ_CORE_ERROR("GLFW Error ({0}) {1}", err, msg);
}

static bool InitializeGLFW()
{
    // GLFW must be initialized exactly once.
    HZ_ASSERT(!s_GLFWInitialized, "Duplicated GLFW initialization.");
    if (glfwInit() == GLFW_TRUE) {
        HZ_CORE_INFO("GLFW initialized");
        s_GLFWInitialized = true;
    }
    return s_GLFWInitialized;
}

/**********************************************************************************************/
/**********************************************************************************************/

Window *Window::Create(const WindowProps &props)
{
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps &props) :
    m_Window(nullptr), m_Data { props.title, props.width, props.height, false }
{
    Init();
}

WindowsWindow::~WindowsWindow()
{
    Shutdown();
}


void WindowsWindow::SetEventCallback(const EventCallbackFn &cb)
{
    m_Data.eventCallback = cb;
}

void WindowsWindow::SetVSync(bool enabled)
{
    glfwSwapInterval(enabled ? 1 : 0);
    m_Data.vsync = enabled;
}

bool WindowsWindow::IsVSync() const
{
    return m_Data.vsync;
}

void WindowsWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void WindowsWindow::Init()
{
    HZ_CORE_INFO("Creating window {0} ({1}, {2}).", m_Data.title, m_Data.width, m_Data.height);

    // Initialize GLFW if needed.
    if (!s_GLFWInitialized && !InitializeGLFW())
        HZ_CORE_ERROR("Failed to initialize GLFW.");
    HZ_ASSERT(s_GLFWInitialized, "GLFW must be initialized.");

    // Set GLFW error callback.
    glfwSetErrorCallback(GLFWErrorCallback);

    m_Window = glfwCreateWindow((int)m_Data.width, (int)m_Data.height, m_Data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    SetVSync(true);

    // Load OpenGL function pointers using Glad.

    int ret = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    HZ_ASSERT(res, "Glad must be initialized.");

    // By binding a pointer to user data to a GLFW window, the bound user data is accessible
    // everywhere the GLFW window is present. In our case, a user pointer is used to synchronize
    // window states between our C++ window representation (struct WindowData) and GLFW's window
    // representation. It also serves as a proxy for translating and relaying GLFW events into
    // Hazel events.

    glfwSetWindowUserPointer(m_Window, &m_Data);

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height)
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

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);
        });

    glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
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

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods)
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

    glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xoffset, double yoffset)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.eventCallback(event);
        });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double x, double y)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)x, (float)y);
            data.eventCallback(event);
        });
}

void WindowsWindow::Shutdown()
{
    glfwDestroyWindow(m_Window);
    m_Window = nullptr;
}

}  // namespace Hazel
