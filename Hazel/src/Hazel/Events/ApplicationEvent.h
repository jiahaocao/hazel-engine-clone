#pragma once

#include "Event.h"

namespace Hazel {

class HAZEL_API WindowResizeEvent : public Event {
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
        ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);

private:
    unsigned int m_Width, m_Height;
};

class HAZEL_API WindowCloseEvent : public Event {
public:
    WindowCloseEvent() { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowCloseEvent";
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowClose);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class HAZEL_API AppTickEvent : public Event {
public:
    AppTickEvent() { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "AppTickEvent";
        return ss.str();
    }

    EVENT_CLASS_TYPE(AppTick);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};


class HAZEL_API AppUpdateEvent : public Event {
public:
    AppUpdateEvent() { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "AppUpdateEvent";
        return ss.str();
    }

    EVENT_CLASS_TYPE(AppUpdate);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class HAZEL_API AppRenderEvent : public Event {
public:
    AppRenderEvent() { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "AppRenderEvent";
        return ss.str();
    }

    EVENT_CLASS_TYPE(AppRender);
    EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

}  // namespace Hazel
