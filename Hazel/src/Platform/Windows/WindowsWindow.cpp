#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel/Log.h"

namespace Hazel {

	// GLFW needs to be initialized only once.
	static bool s_GLFWInitialized = false;

	static bool InitializeGLFW()
	{
		HZ_ASSERT(!s_GLFWInitialized, "Duplicated GLFW initialization.");
		if (glfwInit() == GLFW_TRUE)
			s_GLFWInitialized = true;
		return s_GLFWInitialized;
	}

	/**************************************************************************/

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) :
		m_Window(nullptr), m_Data{ props.title, props.width, props.height, false }
	{
		Init();
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}


	void WindowsWindow::SetEventCallback(const EventCallbackFn& cb)
	{
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

		if (!s_GLFWInitialized && !InitializeGLFW())
			HZ_CORE_ERROR("Could not initialize GLFW.");

		m_Window = glfwCreateWindow((int)m_Data.width, (int)m_Data.height, m_Data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}

}  // namespace Hazel
