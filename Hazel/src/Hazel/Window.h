#pragma once

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

	struct WindowProps {
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(
			const std::string& title = "Hazel Engine",
			unsigned int width = 1280,
			unsigned int height = 720) :
			title(title), width(width), height(height) { }
	};

	// Declaring pure virtual member functions makes a class abstract.
	// Each platform gets its own window class as window management is platform-specific.
	class HAZEL_API Window {
	public:
		static Window* Create(const WindowProps& props = WindowProps());

		virtual ~Window() { }

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		using EventCallbackFn = std::function<void(Event&)>;
		virtual void SetEventCallback(const EventCallbackFn& cb) = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void OnUpdate() = 0;
	};

}  // namespace Hazel
