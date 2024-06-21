#pragma once

#include "Hazel/Core.h"

namespace Hazel {

// Keyboard input is global.

class HAZEL_API InputManager {
public:
    inline static bool IsKeyPressed(int keyCode)
    {
        return s_Instance->IsKeyPressedImpl(keyCode);
    }

    inline static bool IsMouseButtonPressed(int button)
    {
        return s_Instance->IsMouseButtonPressedImpl(button);
    }

    inline static std::pair<float, float> GetMousePosition()
    {
        return s_Instance->GetMousePositionImpl();
    }

    inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
    inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

protected:
    virtual bool IsKeyPressedImpl(int keyCode) = 0;
    virtual bool IsMouseButtonPressedImpl(int button) = 0;
    virtual std::pair<float, float> GetMousePositionImpl() = 0;
    virtual float GetMouseXImpl() = 0;
    virtual float GetMouseYImpl() = 0;

private:
    //InputManager(const InputManager &other) = delete;
    //InputManager &operator=(const InputManager &other) = delete;

    static InputManager *s_Instance;
};

}  // namespace Hazel
