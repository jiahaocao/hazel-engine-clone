#pragma once

#include "Event.h"

namespace Hazel {

class HAZEL_API KeyEvent : public Event {
public:
    inline int GetKeyCode() const { return m_KeyCode; }
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

protected:
    int m_KeyCode;
    KeyEvent(int keyCode) : m_KeyCode(keyCode) { }
};

class HAZEL_API KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int keyCode, int repeatCount)
        : KeyEvent(keyCode), m_RepeatCount(repeatCount) { }

    inline int GetRepeatCount() const { return m_RepeatCount; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << "Event: ";
        ss << m_KeyCode << "(" << m_RepeatCount << " repeats)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)

private:
    int m_RepeatCount;
};

class HAZEL_API KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << "Event: ";
        ss << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

class HAZEL_API KeyCharEvent : public KeyEvent {
public:
    KeyCharEvent(int keyCode) : KeyEvent(keyCode) { }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << GetName() << "Event: ";
        ss << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyChar)
};

}  // namespace Hazel
