#pragma once

#include "Hazel/Layers/Layer.h"
#include "Hazel/Events/KeyEvent.h"
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

    // For each Hazel event that ImGui needs to respond, create a callback function that when the
    // Hazel event occurs, fire the corresponding ImGui event. It is possible to define callbacks
    // as lambda function, but using member functions can be more clear.

    bool OnMouseMovedEvent(MouseMovedEvent &event);
    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event);
    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event);
    bool OnMouseScrolledEvent(MouseScrolledEvent &event);
    bool OnKeyPressedEvent(KeyPressedEvent &event);
    bool OnKeyReleasedEvent(KeyReleasedEvent &event);
    bool OnKeyCharEvent(KeyCharEvent &event);
    bool OnWindowResizeEvent(WindowResizeEvent &event);

private:
    float m_Time = 0.0f;
};

}  // namespace Hazel
