#pragma once

#include "Core.h"
#include "Hazel/Window.h"
#include "Hazel/Layers/LayerStack.h"
#include "Hazel/Events/WindowEvent.h"
#include "Hazel/Events/AppEvent.h"

namespace Hazel {

class HAZEL_API Application {
public:
    Application();
    virtual ~Application();
    void Run();

    void OnEvent(Event &e);

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *overlay);

    static inline Application &Get() { return *s_Instance; }
    inline Window &GetWindow() { return *m_Window; }

private:
    bool m_Running = true;
    std::unique_ptr<Window> m_Window;
    bool OnWindowClose(WindowCloseEvent &e);
    LayerStack m_LayerStack;

    static Application *s_Instance;
};

// To be defined in the client code.
Application *CreateApplication();

}  // namespace Hazel
