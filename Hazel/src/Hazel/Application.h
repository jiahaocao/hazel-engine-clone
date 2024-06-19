#pragma once
#ifndef HAZEL_APPLICATION_H
#define HAZEL_APPLICATION_H

#include "Core.h"
#include "Window.h"

namespace Hazel {

	class HAZEL_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();

	private:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
	};

	// To be defined in the client code.
	Application* CreateApplication();


}

#endif  // HAZEL_APPLICATION_H
