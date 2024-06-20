#pragma once

#include "Event.h"

namespace Hazel {

class HAZEL_API AppEvent : public Event {
public:
    EVENT_CLASS_CATEGORY(EventCategoryApp)
};

class HAZEL_API AppTickEvent : public Event {
public:
    AppTickEvent() { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << "Event";
        return ss.str();
    }

    EVENT_CLASS_TYPE(AppTick);
};


class HAZEL_API AppUpdateEvent : public Event {
public:
    AppUpdateEvent() { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << "Event";
        return ss.str();
    }

    EVENT_CLASS_TYPE(AppUpdate);
};

class HAZEL_API AppRenderEvent : public Event {
public:
    AppRenderEvent() { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << "Event";
        return ss.str();
    }

    EVENT_CLASS_TYPE(AppRender);
};

}  // namespace Hazel
