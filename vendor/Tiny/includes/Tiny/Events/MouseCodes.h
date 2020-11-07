#pragma once

namespace Tiny
{
	typedef enum class MouseCode : unsigned short
	{
		// From glfw3.h
		Button0                = 0,
		Button1                = 1,
		Button2                = 2,
		Button3                = 3,
		Button4                = 4,
		Button5                = 5,
		Button6                = 6,
		Button7                = 7,

		ButtonLast             = Button7,
		ButtonLeft             = Button0,
		ButtonRight            = Button1,
		ButtonMiddle           = Button2
	} Mouse;

	//typedef Tiny::MouseCode Mouse;
	
	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<unsigned short>(mouseCode);
		return os;
	}
}

#define T_MOUSE_BUTTON_0      ::TINY::Mouse::Button0
#define T_MOUSE_BUTTON_1      ::TINY::Mouse::Button1
#define T_MOUSE_BUTTON_2      ::TINY::Mouse::Button2
#define T_MOUSE_BUTTON_3      ::TINY::Mouse::Button3
#define T_MOUSE_BUTTON_4      ::TINY::Mouse::Button4
#define T_MOUSE_BUTTON_5      ::TINY::Mouse::Button5
#define T_MOUSE_BUTTON_6      ::TINY::Mouse::Button6
#define T_MOUSE_BUTTON_7      ::TINY::Mouse::Button7
#define T_MOUSE_BUTTON_LAST   ::TINY::Mouse::ButtonLast
#define T_MOUSE_BUTTON_LEFT   ::TINY::Mouse::ButtonLeft
#define T_MOUSE_BUTTON_RIGHT  ::TINY::Mouse::ButtonRight
#define T_MOUSE_BUTTON_MIDDLE ::TINY::Mouse::ButtonMiddle
