#pragma once

#include <GLFW/glfw3.h>
#include "Hazel/Events/Event.h"

namespace Hazel {

using EventCallbackFn = std::function<void(Event &)>;

struct WindowData {
    std::string title;
    unsigned int width;
    unsigned int height;
    bool vsync;
    EventCallbackFn eventCallback;
};

// An event translation layer.
// Translate GLFW events into Hazel events.

class GLFWData {
public:
    GLFWData(GLFWwindow *window);
    ~GLFWData();

private:

    GLFWwindow *m_Window;
    double m_Time;

    GLFWwindowsizefun   m_CallbackWindowSize    = nullptr;
    GLFWwindowclosefun  m_CallbackWindowClose   = nullptr;
    GLFWcursorposfun    m_CallbackCursorPos     = nullptr;
    GLFWmousebuttonfun  m_CallbackMouseButton   = nullptr;
    GLFWscrollfun       m_CallbackScroll        = nullptr;
    GLFWkeyfun          m_CallbackKey           = nullptr;
    GLFWcharfun         m_CallbackChar          = nullptr;

private:
    void InstallCallbacks();

};

}  // namespace Hazel
