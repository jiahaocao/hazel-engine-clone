#pragma once

#include "Event.h"

namespace Hazel {

class HAZEL_API WindowEvent : public Event {
public:
    EVENT_CLASS_CATEGORY(EventCategoryWindow)
};

class HAZEL_API WindowResizeEvent : public WindowEvent {
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : m_Width(width), m_Height(height)
    {
    }

    inline unsigned int GetWidth() { return m_Width; }
    inline unsigned int GetHeight() { return m_Height; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << "Event: ";
        ss << m_Width << ", " << m_Height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)

private:
    unsigned int m_Width, m_Height;
};

class HAZEL_API WindowCloseEvent : public WindowEvent {
public:
    WindowCloseEvent() { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << "Event";
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowClose);
};

}  // namespace Hazel
