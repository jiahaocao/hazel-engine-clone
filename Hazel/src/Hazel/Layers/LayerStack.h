#pragma once

#include "Hazel/Core.h"
#include "Layer.h"

namespace Hazel {

class HAZEL_API LayerStack {
public:
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer *layer);
    void PopLayer(Layer *layer);

    void PushOverlay(Layer *overlay);
    void PopOverlay(Layer *overlay);

    std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }
    std::vector<Layer *>::iterator end() { return m_Layers.end(); }

private:

    // m_Layers is divided into two parts. The first part consists of layers
    // and the second part consists of overlays. m_LayerInsert points to the
    // beginning of the overlay part (that is, one past the last layer.)

    std::vector<Layer *> m_Layers;
    std::vector<Layer *>::iterator m_LayerInsert;
};

}  // namespace Hazel
