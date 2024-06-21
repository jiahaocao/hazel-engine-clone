#pragma once

#include "Hazel/Input.h"

namespace Hazel {

class WindowsInputManager : public InputManager {
protected:
    virtual bool IsKeyPressedImpl(int keyCode) override;
    virtual bool IsMouseButtonPressedImpl(int button) override;
    virtual std::pair<float, float> GetMousePositionImpl() override;
    virtual float GetMouseXImpl() override;
    virtual float GetMouseYImpl() override;
};

}  // namespace Hazel
