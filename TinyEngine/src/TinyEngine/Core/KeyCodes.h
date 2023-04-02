#pragma once

namespace TinyEngine
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

/* Printable keys */
// From glfw3.h
#define TE_KEY_SPACE           ::TinyEngine::Key::Space
#define TE_KEY_APOSTROPHE      ::TinyEngine::Key::Apostrophe    /* ' */
#define TE_KEY_COMMA           ::TinyEngine::Key::Comma         /* , */
#define TE_KEY_MINUS           ::TinyEngine::Key::Minus         /* - */
#define TE_KEY_PERIOD          ::TinyEngine::Key::Period        /* . */
#define TE_KEY_SLASH           ::TinyEngine::Key::Slash         /* / */
#define TE_KEY_0               ::TinyEngine::Key::D0
#define TE_KEY_1               ::TinyEngine::Key::D1
#define TE_KEY_2               ::TinyEngine::Key::D2
#define TE_KEY_3               ::TinyEngine::Key::D3
#define TE_KEY_4               ::TinyEngine::Key::D4
#define TE_KEY_5               ::TinyEngine::Key::D5
#define TE_KEY_6               ::TinyEngine::Key::D6
#define TE_KEY_7               ::TinyEngine::Key::D7
#define TE_KEY_8               ::TinyEngine::Key::D8
#define TE_KEY_9               ::TinyEngine::Key::D9
#define TE_KEY_SEMICOLON       ::TinyEngine::Key::Semicolon     /* ; */
#define TE_KEY_EQUAL           ::TinyEngine::Key::Equal         /* = */
#define TE_KEY_A               ::TinyEngine::Key::A
#define TE_KEY_B               ::TinyEngine::Key::B
#define TE_KEY_C               ::TinyEngine::Key::C
#define TE_KEY_D               ::TinyEngine::Key::D
#define TE_KEY_E               ::TinyEngine::Key::E
#define TE_KEY_F               ::TinyEngine::Key::F
#define TE_KEY_G               ::TinyEngine::Key::G
#define TE_KEY_H               ::TinyEngine::Key::H
#define TE_KEY_I               ::TinyEngine::Key::I
#define TE_KEY_J               ::TinyEngine::Key::J
#define TE_KEY_K               ::TinyEngine::Key::K
#define TE_KEY_L               ::TinyEngine::Key::L
#define TE_KEY_M               ::TinyEngine::Key::M
#define TE_KEY_N               ::TinyEngine::Key::N
#define TE_KEY_O               ::TinyEngine::Key::O
#define TE_KEY_P               ::TinyEngine::Key::P
#define TE_KEY_Q               ::TinyEngine::Key::Q
#define TE_KEY_R               ::TinyEngine::Key::R
#define TE_KEY_S               ::TinyEngine::Key::S
#define TE_KEY_T               ::TinyEngine::Key::T
#define TE_KEY_U               ::TinyEngine::Key::U
#define TE_KEY_V               ::TinyEngine::Key::V
#define TE_KEY_W               ::TinyEngine::Key::W
#define TE_KEY_X               ::TinyEngine::Key::X
#define TE_KEY_Y               ::TinyEngine::Key::Y
#define TE_KEY_Z               ::TinyEngine::Key::Z
#define TE_KEY_LEFT_BRACKET    ::TinyEngine::Key::LeftBracket   /* [ */
#define TE_KEY_BACKSLASH       ::TinyEngine::Key::Backslash     /* \ */
#define TE_KEY_RIGHT_BRACKET   ::TinyEngine::Key::RightBracket  /* ] */
#define TE_KEY_GRAVE_ACCENT    ::TinyEngine::Key::GraveAccent   /* ` */
#define TE_KEY_WORLD_1         ::TinyEngine::Key::World1        /* non-US #1 */
#define TE_KEY_WORLD_2         ::TinyEngine::Key::World2        /* non-US #2 */

/* Function keys */
#define TE_KEY_ESCAPE          ::TinyEngine::Key::Escape
#define TE_KEY_ENTER           ::TinyEngine::Key::Enter
#define TE_KEY_TAB             ::TinyEngine::Key::Tab
#define TE_KEY_BACKSPACE       ::TinyEngine::Key::Backspace
#define TE_KEY_INSERT          ::TinyEngine::Key::Insert
#define TE_KEY_DELETE          ::TinyEngine::Key::Delete
#define TE_KEY_RIGHT           ::TinyEngine::Key::Right
#define TE_KEY_LEFT            ::TinyEngine::Key::Left
#define TE_KEY_DOWN            ::TinyEngine::Key::Down
#define TE_KEY_UP              ::TinyEngine::Key::Up
#define TE_KEY_PAGE_UP         ::TinyEngine::Key::PageUp
#define TE_KEY_PAGE_DOWN       ::TinyEngine::Key::PageDown
#define TE_KEY_HOME            ::TinyEngine::Key::Home
#define TE_KEY_END             ::TinyEngine::Key::End
#define TE_KEY_CAPS_LOCK       ::TinyEngine::Key::CapsLock
#define TE_KEY_SCROLL_LOCK     ::TinyEngine::Key::ScrollLock
#define TE_KEY_NUM_LOCK        ::TinyEngine::Key::NumLock
#define TE_KEY_PRINT_SCREEN    ::TinyEngine::Key::PrintScreen
#define TE_KEY_PAUSE           ::TinyEngine::Key::Pause
#define TE_KEY_F1              ::TinyEngine::Key::F1
#define TE_KEY_F2              ::TinyEngine::Key::F2
#define TE_KEY_F3              ::TinyEngine::Key::F3
#define TE_KEY_F4              ::TinyEngine::Key::F4
#define TE_KEY_F5              ::TinyEngine::Key::F5
#define TE_KEY_F6              ::TinyEngine::Key::F6
#define TE_KEY_F7              ::TinyEngine::Key::F7
#define TE_KEY_F8              ::TinyEngine::Key::F8
#define TE_KEY_F9              ::TinyEngine::Key::F9
#define TE_KEY_F10             ::TinyEngine::Key::F10
#define TE_KEY_F11             ::TinyEngine::Key::F11
#define TE_KEY_F12             ::TinyEngine::Key::F12
#define TE_KEY_F13             ::TinyEngine::Key::F13
#define TE_KEY_F14             ::TinyEngine::Key::F14
#define TE_KEY_F15             ::TinyEngine::Key::F15
#define TE_KEY_F16             ::TinyEngine::Key::F16
#define TE_KEY_F17             ::TinyEngine::Key::F17
#define TE_KEY_F18             ::TinyEngine::Key::F18
#define TE_KEY_F19             ::TinyEngine::Key::F19
#define TE_KEY_F20             ::TinyEngine::Key::F20
#define TE_KEY_F21             ::TinyEngine::Key::F21
#define TE_KEY_F22             ::TinyEngine::Key::F22
#define TE_KEY_F23             ::TinyEngine::Key::F23
#define TE_KEY_F24             ::TinyEngine::Key::F24
#define TE_KEY_F25             ::TinyEngine::Key::F25

/* Keypad */
#define TE_KEY_KP_0            ::TinyEngine::Key::KP0
#define TE_KEY_KP_1            ::TinyEngine::Key::KP1
#define TE_KEY_KP_2            ::TinyEngine::Key::KP2
#define TE_KEY_KP_3            ::TinyEngine::Key::KP3
#define TE_KEY_KP_4            ::TinyEngine::Key::KP4
#define TE_KEY_KP_5            ::TinyEngine::Key::KP5
#define TE_KEY_KP_6            ::TinyEngine::Key::KP6
#define TE_KEY_KP_7            ::TinyEngine::Key::KP7
#define TE_KEY_KP_8            ::TinyEngine::Key::KP8
#define TE_KEY_KP_9            ::TinyEngine::Key::KP9
#define TE_KEY_KP_DECIMAL      ::TinyEngine::Key::KPDecimal
#define TE_KEY_KP_DIVIDE       ::TinyEngine::Key::KPDivide
#define TE_KEY_KP_MULTIPLY     ::TinyEngine::Key::KPMultiply
#define TE_KEY_KP_SUBTRACT     ::TinyEngine::Key::KPSubtract
#define TE_KEY_KP_ADD          ::TinyEngine::Key::KPAdd
#define TE_KEY_KP_ENTER        ::TinyEngine::Key::KPEnter
#define TE_KEY_KP_EQUAL        ::TinyEngine::Key::KPEqual

#define TE_KEY_LEFT_SHIFT      ::TinyEngine::Key::LeftShift
#define TE_KEY_LEFT_CONTROL    ::TinyEngine::Key::LeftControl
#define TE_KEY_LEFT_ALT        ::TinyEngine::Key::LeftAlt
#define TE_KEY_LEFT_SUPER      ::TinyEngine::Key::LeftSuper
#define TE_KEY_RIGHT_SHIFT     ::TinyEngine::Key::RightShift
#define TE_KEY_RIGHT_CONTROL   ::TinyEngine::Key::RightControl
#define TE_KEY_RIGHT_ALT       ::TinyEngine::Key::RightAlt
#define TE_KEY_RIGHT_SUPER     ::TinyEngine::Key::RightSuper
#define TE_KEY_MENU            ::TinyEngine::Key::Menu