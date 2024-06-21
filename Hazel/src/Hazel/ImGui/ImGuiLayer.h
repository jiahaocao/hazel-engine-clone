#pragma once

#include "Hazel/Layers/Layer.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/WindowEvent.h"

namespace Hazel {

class HAZEL_API ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void OnAttach();
    virtual void OnDetach();
    virtual void OnUpdate();
    virtual void OnEvent(Event &event);

private:
    bool OnMouseMovedEvent(MouseMovedEvent &event);
    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event);
    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event);
    bool OnMouseScrolledEvent(MouseScrolledEvent &event);
    bool OnWindowResizeEvent(WindowResizeEvent &event);

private:
    float m_Time = 0.0f;
};

}  // namespace Hazel
