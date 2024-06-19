#include "hzpch.h"
#include "Application.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace Hazel {

	Application::Application() :
		m_Window(Window::Create()) {
	
		m_Window->SetEventCallback(
			std::bind(&Application::OnEvent, this, std::placeholders::_1)
		);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running) {
			glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBegin(GL_TRIANGLES);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f(0.5f, -0.5f);
			glVertex2f(0.0f, 0.5f);
			glEnd();

			m_Window->OnUpdate();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
		}
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(
			std::bind(&Application::OnWindowClose, this, std::placeholders::_1)
		);
		HZ_CORE_INFO("{0}", e.ToString());

		//// Overlays should handle the event first.
		//for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
		//	(*--it)->OnEvent(e);
		//	if (e.IsHandled())
		//		break;
		//}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
