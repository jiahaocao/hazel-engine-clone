#pragma once

#include <GLFW/glfw3.h>
#include "Hazel/Window.h"

namespace Hazel {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();

		inline unsigned int GetWidth() const override { return m_Data.width; }
		inline unsigned int GetHeight() const override { return m_Data.height; }

		virtual void SetEventCallback(const EventCallbackFn& cb) override;

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		void OnUpdate() override;


	private:
		virtual void Init();
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window = nullptr;

		struct WindowData {
			std::string title;
			unsigned int width;
			unsigned int height;
			bool vsync;
			EventCallbackFn eventCallback;
		};

		WindowData m_Data;
	};

}  // namespace Hazel
