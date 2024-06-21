#pragma once

#include <GLFW/glfw3.h>
#include "Hazel/Window.h"
#include "GLFW2Hazel.h"

namespace Hazel {

class WindowsWindow : public Window {
public:
    WindowsWindow(const WindowProps &props);

    virtual ~WindowsWindow();

    inline unsigned int GetWidth() const override { return m_Data.width; }
    inline unsigned int GetHeight() const override { return m_Data.height; }

    virtual void SetEventCallback(const EventCallbackFn &cb) override;

    virtual void SetVSync(bool enabled) override;
    virtual bool IsVSync() const override;

    void OnUpdate() override;

    GLFWwindow *GetGLFWWindow() const { return m_Window; }

private:
    virtual void Init();
    virtual void Shutdown();

private:
    GLFWwindow *m_Window = nullptr;
    WindowData m_Data;

    std::unique_ptr<GLFWData> m_GLFWData;
};

}  // namespace Hazel
