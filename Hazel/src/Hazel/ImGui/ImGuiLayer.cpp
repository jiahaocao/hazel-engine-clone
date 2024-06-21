#include "hzpch.h"
#include "ImGuiLayer.h"

#include <imgui.h>
#include <GLFW/glfw3.h>
#include "Platform/OpenGL/imgui_impl_glfw.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Hazel/Application.h"
#include "Hazel/Events/Event.h"

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


static ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int key);

namespace Hazel {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
{
}

ImGuiLayer::~ImGuiLayer()
{
}

void ImGuiLayer::OnAttach()
{
    const char *glsl_version = "#version 130";
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO &io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach()
{

}

void ImGuiLayer::OnUpdate()
{
    Application &app = Application::Get();
    ImGuiIO &io = ImGui::GetIO();

    io.DisplaySize = ImVec2(
        app.GetWindow().GetWidth(),
        app.GetWindow().GetHeight());

    float time = (float)glfwGetTime();
    io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Begin("Window");
    ImGui::Text("hello there.");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// When ImGuiLayer receives an event, it 

void ImGuiLayer::OnEvent(Event &event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
    dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMousePosEvent(event.GetX(), event.GetY());
    return false;
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseButtonEvent(event.GetMouseButton(), true);
    return false;
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseButtonEvent(event.GetMouseButton(), false);
    return false;
}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    io.AddMouseWheelEvent(event.GetXOffset(), event.GetYOffset());
    return false;
}

bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent &event)
{
    ImGuiIO &io = ImGui::GetIO();
    return false;
}

}  // namespace Hazel
