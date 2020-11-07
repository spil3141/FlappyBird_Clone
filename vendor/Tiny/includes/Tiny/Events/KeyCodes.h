#pragma once

namespace Tiny
{
	typedef enum class KeyCode : unsigned short
	{
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	}Key;

	//typedef Tiny::KeyCode Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<unsigned int>(keyCode);
		return os;
	}
}

// From glfw3.h
#define T_KEY_SPACE           ::Tiny::Key::Space
#define T_KEY_APOSTROPHE      ::Tiny::Key::Apostrophe    /* ' */
#define T_KEY_COMMA           ::Tiny::Key::Comma         /* , */
#define T_KEY_MINUS           ::Tiny::Key::Minus         /* - */
#define T_KEY_PERIOD          ::Tiny::Key::Period        /* . */
#define T_KEY_SLASH           ::Tiny::Key::Slash         /* / */
#define T_KEY_0               ::Tiny::Key::D0
#define T_KEY_1               ::Tiny::Key::D1
#define T_KEY_2               ::Tiny::Key::D2
#define T_KEY_3               ::Tiny::Key::D3
#define T_KEY_4               ::Tiny::Key::D4
#define T_KEY_5               ::Tiny::Key::D5
#define T_KEY_6               ::Tiny::Key::D6
#define T_KEY_7               ::Tiny::Key::D7
#define T_KEY_8               ::Tiny::Key::D8
#define T_KEY_9               ::Tiny::Key::D9
#define T_KEY_SEMICOLON       ::Tiny::Key::Semicolon     /* ; */
#define T_KEY_EQUAL           ::Tiny::Key::Equal         /* = */
#define T_KEY_A               ::Tiny::Key::A
#define T_KEY_B               ::Tiny::Key::B
#define T_KEY_C               ::Tiny::Key::C
#define T_KEY_D               ::Tiny::Key::D
#define T_KEY_E               ::Tiny::Key::E
#define T_KEY_F               ::Tiny::Key::F
#define T_KEY_G               ::Tiny::Key::G
#define T_KEY_H               ::Tiny::Key::H
#define T_KEY_I               ::Tiny::Key::I
#define T_KEY_J               ::Tiny::Key::J
#define T_KEY_K               ::Tiny::Key::K
#define T_KEY_L               ::Tiny::Key::L
#define T_KEY_M               ::Tiny::Key::M
#define T_KEY_N               ::Tiny::Key::N
#define T_KEY_O               ::Tiny::Key::O
#define T_KEY_P               ::Tiny::Key::P
#define T_KEY_Q               ::Tiny::Key::Q
#define T_KEY_R               ::Tiny::Key::R
#define T_KEY_S               ::Tiny::Key::S
#define T_KEY_T               ::Tiny::Key::T
#define T_KEY_U               ::Tiny::Key::U
#define T_KEY_V               ::Tiny::Key::V
#define T_KEY_W               ::Tiny::Key::W
#define T_KEY_X               ::Tiny::Key::X
#define T_KEY_Y               ::Tiny::Key::Y
#define T_KEY_Z               ::Tiny::Key::Z
#define T_KEY_LEFT_BRACKET    ::Tiny::Key::LeftBracket   /* [ */
#define T_KEY_BACKSLASH       ::Tiny::Key::Backslash     /* \ */
#define T_KEY_RIGHT_BRACKET   ::Tiny::Key::RightBracket  /* ] */
#define T_KEY_GRAVE_ACCENT    ::Tiny::Key::GraveAccent   /* ` */
#define T_KEY_WORLD_1         ::Tiny::Key::World1        /* non-US #1 */
#define T_KEY_WORLD_2         ::Tiny::Key::World2        /* non-US #2 */

/* Function keys */
#define T_KEY_ESCAPE          ::Tiny::Key::Escape
#define T_KEY_ENTER           ::Tiny::Key::Enter
#define T_KEY_TAB             ::Tiny::Key::Tab
#define T_KEY_BACKSPACE       ::Tiny::Key::Backspace
#define T_KEY_INSERT          ::Tiny::Key::Insert
#define T_KEY_DELETE          ::Tiny::Key::Delete
#define T_KEY_RIGHT           ::Tiny::Key::Right
#define T_KEY_LEFT            ::Tiny::Key::Left
#define T_KEY_DOWN            ::Tiny::Key::Down
#define T_KEY_UP              ::Tiny::Key::Up
#define T_KEY_PAGE_UP         ::Tiny::Key::PageUp
#define T_KEY_PAGE_DOWN       ::Tiny::Key::PageDown
#define T_KEY_HOME            ::Tiny::Key::Home
#define T_KEY_END             ::Tiny::Key::End
#define T_KEY_CAPS_LOCK       ::Tiny::Key::CapsLock
#define T_KEY_SCROLL_LOCK     ::Tiny::Key::ScrollLock
#define T_KEY_NUM_LOCK        ::Tiny::Key::NumLock
#define T_KEY_PRINT_SCREEN    ::Tiny::Key::PrintScreen
#define T_KEY_PAUSE           ::Tiny::Key::Pause
#define T_KEY_F1              ::Tiny::Key::F1
#define T_KEY_F2              ::Tiny::Key::F2
#define T_KEY_F3              ::Tiny::Key::F3
#define T_KEY_F4              ::Tiny::Key::F4
#define T_KEY_F5              ::Tiny::Key::F5
#define T_KEY_F6              ::Tiny::Key::F6
#define T_KEY_F7              ::Tiny::Key::F7
#define T_KEY_F8              ::Tiny::Key::F8
#define T_KEY_F9              ::Tiny::Key::F9
#define T_KEY_F10             ::Tiny::Key::F10
#define T_KEY_F11             ::Tiny::Key::F11
#define T_KEY_F12             ::Tiny::Key::F12
#define T_KEY_F13             ::Tiny::Key::F13
#define T_KEY_F14             ::Tiny::Key::F14
#define T_KEY_F15             ::Tiny::Key::F15
#define T_KEY_F16             ::Tiny::Key::F16
#define T_KEY_F17             ::Tiny::Key::F17
#define T_KEY_F18             ::Tiny::Key::F18
#define T_KEY_F19             ::Tiny::Key::F19
#define T_KEY_F20             ::Tiny::Key::F20
#define T_KEY_F21             ::Tiny::Key::F21
#define T_KEY_F22             ::Tiny::Key::F22
#define T_KEY_F23             ::Tiny::Key::F23
#define T_KEY_F24             ::Tiny::Key::F24
#define T_KEY_F25             ::Tiny::Key::F25

/* Keypad */
#define T_KEY_KP_0            ::Tiny::Key::KP0
#define T_KEY_KP_1            ::Tiny::Key::KP1
#define T_KEY_KP_2            ::Tiny::Key::KP2
#define T_KEY_KP_3            ::Tiny::Key::KP3
#define T_KEY_KP_4            ::Tiny::Key::KP4
#define T_KEY_KP_5            ::Tiny::Key::KP5
#define T_KEY_KP_6            ::Tiny::Key::KP6
#define T_KEY_KP_7            ::Tiny::Key::KP7
#define T_KEY_KP_8            ::Tiny::Key::KP8
#define T_KEY_KP_9            ::Tiny::Key::KP9
#define T_KEY_KP_DECIMAL      ::Tiny::Key::KPDecimal
#define T_KEY_KP_DIVIDE       ::Tiny::Key::KPDivide
#define T_KEY_KP_MULTIPLY     ::Tiny::Key::KPMultiply
#define T_KEY_KP_SUBTRACT     ::Tiny::Key::KPSubtract
#define T_KEY_KP_ADD          ::Tiny::Key::KPAdd
#define T_KEY_KP_ENTER        ::Tiny::Key::KPEnter
#define T_KEY_KP_EQUAL        ::Tiny::Key::KPEqual

#define T_KEY_LEFT_SHIFT      ::Tiny::Key::LeftShift
#define T_KEY_LEFT_CONTROL    ::Tiny::Key::LeftControl
#define T_KEY_LEFT_ALT        ::Tiny::Key::LeftAlt
#define T_KEY_LEFT_SUPER      ::Tiny::Key::LeftSuper
#define T_KEY_RIGHT_SHIFT     ::Tiny::Key::RightShift
#define T_KEY_RIGHT_CONTROL   ::Tiny::Key::RightControl
#define T_KEY_RIGHT_ALT       ::Tiny::Key::RightAlt
#define T_KEY_RIGHT_SUPER     ::Tiny::Key::RightSuper
#define T_KEY_MENU            ::Tiny::Key::Menu
