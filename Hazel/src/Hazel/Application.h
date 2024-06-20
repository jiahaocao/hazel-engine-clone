#pragma once

#include "Core.h"
#include "Hazel/Window.h"
#include "Hazel/Layers/LayerStack.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel {

class HAZEL_API Application {
public:
    Application();
    virtual ~Application();
    void Run();

    void OnEvent(Event &e);

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *overlay);

private:
    bool m_Running = true;
    std::unique_ptr<Window> m_Window;
    bool OnWindowClose(WindowCloseEvent &e);
    LayerStack m_LayerStack;
};

// To be defined in the client code.
Application *CreateApplication();

}  // namespace Hazel
