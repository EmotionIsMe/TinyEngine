#pragma once

#include "tepch.h"
#include "TinyEngine/Core/Core.h"

namespace TinyEngine {
	
	// Events in TinyEngine are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	// 事件的详细类型
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,   // Window五种操作
		AppTick, AppUpdate, AppRender,											// APP 的操作，暂时先不管
		KeyPressed, KeyReleased, KeyTyped,										// KeyBoard 的操作
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled      // Mouse 的操作
	};

	// 事件的大体种类
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

	// #define EVENT_CLASS_TYPE

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
		friend class EventDispatcher;
	public:
		bool Handled = false;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:
		
	};
	class EventDispatcher 
	{

		template<typename T>
		using EventFn = std::function <bool(T&)>;  // EventFn 存储了一个输入为任意类型的引用，返回值为bool的函数指针
	public:
		EventDispatcher(Event& event) 
			: m_Event(event)
		{
		}

		// T指的是事件类型, 如果输入的类型没有GetStaticType会报错
		template<typename T>
		bool Dispatch(EventFn<T> func) 
		{
			
			if (m_Event.GetEventType() == T::GetStaticType()) 
			{
				m_Event.Handled = func(*(T*)&m_Event);  //使用(T*)把m_Event转换成输入事件的指针类型
				return true;
			}
			return false;
		}
	private:
		Event&  m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}