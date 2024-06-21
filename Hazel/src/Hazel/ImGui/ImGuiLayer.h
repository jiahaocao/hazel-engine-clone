#pragma once

#include "Hazel/Layers/Layer.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/WindowEvent.h"

namespace Hazel {

class HAZEL_API ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void OnEvent(Event &event) override;

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
