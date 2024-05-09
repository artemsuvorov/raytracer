#pragma once

namespace Core {

enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication    = 1 << 0,
    EventCategoryInput          = 1 << 1,
    EventCategoryKeyboard       = 1 << 2,
    EventCategoryMouse          = 1 << 3,
    EventCategoryMouseButton    = 1 << 4,
};

#ifndef EVENT_CLASS_TYPE
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
#endif

#ifndef EVENT_CLASS_CATEGORY
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
#endif

class Event
{
public:
    virtual ~Event() = default;

    bool Handled = false;

    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

    bool IsInCategory(EventCategory category)
    {
        return GetCategoryFlags() & category;
    }
};

#ifndef BIND_FN
#define BIND_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#endif

class EventDispatcher final
{
public:
    EventDispatcher(Event& event) : m_Event(event)
    {
    }
    
    // Type `F` will be deduced by the compiler.
    template<typename T, typename F>
    bool Dispatch(const F& func)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.Handled |= func(static_cast<T&>(m_Event));
            return true;
        }
        return false;
    }

private:
    Event& m_Event;
};

}
