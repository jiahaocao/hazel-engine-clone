#pragma once

#include "Log.h"

extern Hazel::Application *Hazel::CreateApplication();

int main(int argc, char *argv[])
{
    Hazel::Log::Init();

    HZ_CORE_INFO("Log initialized");
    HZ_INFO("Hello! Var={0:.1f}", 3.14);
    HZ_WARN("Hello! Var={0:.1f}", 3.14);

    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}
