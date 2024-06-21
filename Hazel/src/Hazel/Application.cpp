#include "hzpch.h"
#include "Application.h"
#include "Hazel/Log.h"

#include <glad/glad.h>
#include "Hazel/Input.h"
#include "Hazel/Defines/KeyCodes.h"
#include "Hazel/Defines/MouseButtonCodes.h"

namespace Hazel {

Application *Application::s_Instance = nullptr;

Application::Application() :
    m_Window(Window::Create())
{
    HZ_CORE_ASSERT(s_Instance == nullptr, "Can only have one application.")
    s_Instance = this;
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

        for (Layer *layer : m_LayerStack)
            layer->OnUpdate();

        m_Window->OnUpdate();
    }
}

void Application::OnEvent(Event &event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(
        std::bind(&Application::OnWindowClose, this, std::placeholders::_1)
    );

    HZ_CORE_INFO("{0}", event.ToString());

    // Events are pass to overlays first.
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
        (*--it)->OnEvent(event);
        if (event.IsHandled())
            break;
    }
}

void Application::PushLayer(Layer *layer)
{
    m_LayerStack.PushLayer(layer);
}

void Application::PushOverlay(Layer *overlay)
{
    m_LayerStack.PushOverlay(overlay);
}

bool Application::OnWindowClose(WindowCloseEvent &event)
{
    m_Running = false;
    return true;
}

}  // namespace Hazel
