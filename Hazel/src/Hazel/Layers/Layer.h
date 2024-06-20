#pragma once

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

// Events propagate through layers. If an event is handled by a layer, the layers that follow won't
// receive the event. For example, we don't want our player character to react to a mouse pressed
// event if the click is on a UI element and is handled by a UI layer.

class HAZEL_API Layer {
public:
    Layer(const std::string &name = "Layer");
    virtual ~Layer();

    virtual void OnAttach() { }
    virtual void OnDetach() { }
    virtual void OnUpdate() { }
    virtual void OnEvent(Event &event) { }

    inline const std::string &GetName() { return m_DebugName; }

private:
    std::string m_DebugName;
};

}  // namespace Hazel
