#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {

LayerStack::LayerStack() : m_LayerInsert(m_Layers.begin()) { }

LayerStack::~LayerStack()
{
    for (Layer *layer : m_Layers)
        delete layer;
}

void LayerStack::PushLayer(Layer *layer)
{
    m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
    layer->OnAttach();
}

void LayerStack::PopLayer(Layer *layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
        --m_LayerInsert;
    }
}

void LayerStack::PushOverlay(Layer *layer)
{
    m_Layers.emplace_back(layer);
    layer->OnAttach();
}

void LayerStack::PopOverlay(Layer *layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end())
        m_Layers.erase(it);
}

}  // namespace Hazel
