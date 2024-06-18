#pragma once
#ifndef HAZEL_ENTRY_POINT_H
#define HAZEL_ENTRY_POINT_H

#include <iostream>

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char* argv[])
{
	std::cout << "Hazel engine entry point." << std::endl;
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif  // HAZEL_ENTRY_POINT_H
