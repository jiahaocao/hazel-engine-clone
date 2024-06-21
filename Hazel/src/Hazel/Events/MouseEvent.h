#pragma once

#include "Event.h"

namespace Hazel {

class HAZEL_API MouseEvent : public Event {
public:
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
};

class HAZEL_API MouseMovedEvent : public MouseEvent {
public:
    MouseMovedEvent(float x, float y) : m_PosX(x), m_PosY(y) { }

    inline float GetX() const { return m_PosX; }
    inline float GetY() const { return m_PosY; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << "Event: ";
        ss << m_PosX << ", " << m_PosY;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)

private:
    float m_PosX, m_PosY;
};

class HAZEL_API MouseScrolledEvent : public MouseEvent {
public:
    MouseScrolledEvent(float xofs, float yofs) : m_OffsetX(xofs), m_OffsetY(yofs) { }

    inline float GetXOffset() const { return m_OffsetX; }
    inline float GetYOffset() const { return m_OffsetY; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << "Event: ";
        ss << m_OffsetX << ", " << m_OffsetY;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled);

private:
    float m_OffsetX, m_OffsetY;
};

class HAZEL_API MouseButtonEvent : public MouseEvent {
public:
    inline int GetMouseButton() const { return m_Button; }

protected:
    MouseButtonEvent(int button) : m_Button(button) { }
    int m_Button;
};


class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << "Event: ";
        ss << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed);
};

class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << "Event: ";
        ss << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased);
};

}  // namespace Hazel
