#pragma once
#ifndef HAZEL_APPLICATION_H
#define HAZEL_APPLICATION_H

#include "Core.h"

namespace Hazel {

	class HAZEL_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	// To be defined in the client code.
	Application* CreateApplication();
}

#endif  // HAZEL_APPLICATION_H
