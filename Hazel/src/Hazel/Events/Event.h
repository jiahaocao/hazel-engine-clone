#pragma once

#include "Hazel/Core.h"

namespace Hazel {

// Events are currently blocking, meaning when an event occurs it immediately gets dispatched
// and must be dealt with right away. For the future, a better strategy might be to buffer
// events in an event bus and process them during the "event part" of the update stage.

enum class EventType {
    None = 0,
    WindowClose, WindowResize,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyChar,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

// When declaring enumerations, "enum class" is generally preferred. However, in our case, an
// event may be in multiple categories and we need to perform bitwise operations (&) to check
// which categories an event is in. Because "enum class" does not support implicit conversion,
// "enum" is used for being more convenient. Note that when declaring enumerations using "enum",
// the best practice is to prefix each name with the name of the "enum". This reduces the risk
// of naming conflict.

enum EventCategory {
    None = 0,
    EventCategoryApp            = BIT(0),
    EventCategoryInput          = BIT(1),
    EventCategoryKeyboard       = BIT(2),
    EventCategoryMouse          = BIT(3),
    EventCategoryMouseButton    = BIT(4),
    EventCategoryWindow         = BIT(5),
};

#define EVENT_CLASS_TYPE(type)                                              \
static EventType GetStaticType() { return EventType::##type; }              \
virtual EventType GetType() const override { return GetStaticType(); }      \
virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(categories)                                    \
static int GetStaticCategories() { return categories; }                     \
virtual int GetCategories() const override { return categories; }

/**********************************************************************************************/
/**********************************************************************************************/

class HAZEL_API Event {
public:
    virtual const char *GetName() const = 0;
    virtual EventType GetType() const = 0;
    virtual int GetCategories() const = 0;
    virtual std::string ToString() const { return GetName(); }

    inline bool IsInCategory(EventCategory category) const
    {
        return GetCategories() & category;
    }

    inline bool IsHandled() const { return m_Handled; }

protected:
    bool m_Handled = false;

private:
    friend class EventDispatcher;
};

class EventDispatcher {
private:
    template<typename T>
    using EventFn = std::function<bool(T &)>;

private:
    Event &m_Event;

public:
    EventDispatcher(Event &event) : m_Event(event) { }

    template<typename T>
    bool Dispatch(EventFn<T> func)
    {
        if (m_Event.GetType() == T::GetStaticType()) {
            m_Event.m_Handled = func(*(T *)&m_Event);
            return true;
        }
        return false;
    }
};
 
inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
    return os << e.ToString();
}

}  // namespace Hazel
