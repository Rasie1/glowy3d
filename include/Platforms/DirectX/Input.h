/****************************************************************************
This file is part of glowy3d.

Copyright (c) 2014 Kvachev 'Rasie1' V. D.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#pragma once
#ifdef R_D3D
#include <functional>

namespace glowy3d
{

class Input
{
public:
	enum PressType : ubyte
	{
		press,
		release,
		hold
	};
	
	enum Keyboard
	{
		escape        = 0x01,
		num1          = 0x02,
		num2          = 0x03,
		num3          = 0x04,
		num4          = 0x05,
		num5          = 0x06,
		num6          = 0x07,
		num7          = 0x08,
		num8          = 0x09,
		num9          = 0x0A,
		num0          = 0x0B,
		minus         = 0x0C    /* - on main keyboard */,
		equals        = 0x0D,
		back          = 0x0E    /* backspace */,
		tab           = 0x0F,
		q             = 0x10,
		w             = 0x11,
		e             = 0x12,
		r             = 0x13,
		t             = 0x14,
		y             = 0x15,
		u             = 0x16,
		i             = 0x17,
		o             = 0x18,
		p             = 0x19,
		lbracket      = 0x1A,
		rbracket      = 0x1B,
		enter         = 0x1C    /* Enter on main keyboard */,
		lctrl         = 0x1D,
		a             = 0x1E,
		s             = 0x1F,
		d             = 0x20,
		f             = 0x21,
		g             = 0x22,
		h             = 0x23,
		j             = 0x24,
		k             = 0x25,
		l             = 0x26,
		semicolon     = 0x27,
		apostrophe    = 0x28,
		grave         = 0x29    /* accent grave */,
		lshift        = 0x2A,
		backslash     = 0x2B,
		z             = 0x2C,
		x             = 0x2D,
		c             = 0x2E,
		v             = 0x2F,
		b             = 0x30,
		n             = 0x31,
		m             = 0x32,
		comma         = 0x33,
		period        = 0x34    /* . on main keyboard */,
		slash         = 0x35    /* / on main keyboard */,
		rshift        = 0x36,
		numpadMultiply= 0x37    /* * on numeric keypad */,
		lmenu         = 0x38    /* left alt */,
		space         = 0x39,
		capital       = 0x3A,
		F1            = 0x3B,
		F2            = 0x3C,
		F3            = 0x3D,
		F4            = 0x3E,
		F5            = 0x3F,
		F6            = 0x40,
		F7            = 0x41,
		F8            = 0x42,
		F9            = 0x43,
		F10           = 0x44,
		numlock       = 0x45,
		scroll        = 0x46    /* scroll lock */,
		numpad7       = 0x47,
		numpad8       = 0x48,
		numpad9       = 0x49,
		numpadSubtract= 0x4A    /* - on numeric keypad */,
		numpad4       = 0x4B,
		numpad5       = 0x4C,
		numpad6       = 0x4D,
		numpadAdd     = 0x4E    /* + on numeric keypad */,
		numpad1       = 0x4F,
		numpad2       = 0x50,
		numpad3       = 0x51,
		numpad0       = 0x52,
		numpadDecimal = 0x53    /* . on numeric keypad */,
		oem_102       = 0x56    /* <> or \| on RT 102-key keyboard (Non-U.S.) */,
		F11           = 0x57,
		F12           = 0x58,
		F13           = 0x64    /*                     (NEC PC98) */,
		F14           = 0x65    /*                     (NEC PC98) */,
		F15           = 0x66    /*                     (NEC PC98) */,
		kana          = 0x70    /* (japanese keyboard)            */,
		abnt_c1       = 0x73    /* /? on brazilian keyboard */,
		convert       = 0x79    /* (japanese keyboard)            */,
		noconvert     = 0x7B    /* (Japanese keyboard)            */,
		yen           = 0x7D    /* (Japanese keyboard)            */,
		abnt_c2       = 0x7E    /* Numpad . on Brazilian keyboard */,
		numpadEqual   = 0x8D    /* = on numeric keypad (NEC PC98) */,
		prevtrack     = 0x90    /* previous track (circumflex on japanese keyboard) */,
		at            = 0x91    /*                     (nec pc98) */,
		colon         = 0x92    /*                     (nec pc98) */,
		underline     = 0x93    /*                     (nec pc98) */,
		kanji         = 0x94    /* (japanese keyboard)            */,
		stop          = 0x95    /*                     (nec pc98) */,
		ax            = 0x96    /*                     (japan ax) */,
		unlabeled     = 0x97    /*                        (j3100) */,
		nexttrack     = 0x99    /* next track */,
		numpadEnter   = 0x9C    /* Enter on numeric keypad */,
		rctrl         = 0x9D,
		mute          = 0xA0    /* Mute */,
		calculator    = 0xA1    /* Calculator */,
		playpause     = 0xA2    /* Play / Pause */,
		mediastop     = 0xA4    /* Media Stop */,
		volumedown    = 0xAE    /* Volume - */,
		volumeup      = 0xB0    /* Volume + */,
		webhome       = 0xB2    /* Web home */,
		numpadComma   = 0xB3    /* , on numeric keypad (NEC PC98) */,
		numpadDivide  = 0xB5    /* / on numeric keypad */,
		sysrq         = 0xB7,
		rmenu         = 0xB8    /* right Alt */,
		pause         = 0xC5    /* Pause */,
		home          = 0xC7    /* Home on arrow keypad */,
		up            = 0xC8    /* UpArrow on arrow keypad */,
		prior         = 0xC9    /* PgUp on arrow keypad */,
		left          = 0xCB    /* LeftArrow on arrow keypad */,
		right         = 0xCD    /* RightArrow on arrow keypad */,
		end           = 0xCF    /* End on arrow keypad */,
		down          = 0xD0    /* DownArrow on arrow keypad */,
		next          = 0xD1    /* PgDn on arrow keypad */,
		insert        = 0xD2    /* Insert on arrow keypad */,
		del           = 0xD3    /* Delete on arrow keypad */,
		lwin          = 0xDB    /* Left Windows key */,
		rwin          = 0xDC    /* Right Windows key */,
		apps          = 0xDD    /* AppMenu key */,
		power         = 0xDE    /* System Power */,
		sleep         = 0xDF    /* System Sleep */,
		wake          = 0xE3    /* System Wake */,
		websearch     = 0xE5    /* Web Search */,
		webfavorites  = 0xE6    /* Web Favorites */,
		webrefresh    = 0xE7    /* Web Refresh */,
		webstop       = 0xE8    /* Web Stop */,
		webforward    = 0xE9    /* Web Forward */,
		webback       = 0xEA    /* Web Back */,
		mycomputer    = 0xEB    /* My Computer */,
		mail          = 0xEC    /* Mail */,
		mediaselect   = 0xED    /* Media Select */
		,
		backspace     = back            /* backspace */,
		lalt          = lmenu           /* left alt */,
		capslock      = capital         /* capslock */,
		ralt          = rmenu           /* right alt */,
		uparrow       = up              /* uparrow on arrow keypad */,
		pgup          = prior           /* pgup on arrow keypad */,
		leftarrow     = left            /* leftarrow on arrow keypad */,
		rightarrow    = right           /* rightarrow on arrow keypad */,
		downarrow     = down            /* downarrow on arrow keypad */,
		pgdn          = next            /* pgdn on arrow keypad */
		,
		circumflex    = prevtrack       /* japanese keyboard */,

		last = 0xFF,
	};

	static void process();
	static void init();
	static void deinit();
	static void setUpDefaultControls();
	static bool getKey(Keyboard key);
	static void setKeyCallback(Keyboard key, PressType type, std::function<void()> callback);
	static void resetKeyCallback(Keyboard key, PressType type);

	friend class System;
	friend class EngineInitialization;

private:
	Input() {}
	~Input() {}

	//thread-unsafe?
	static std::function<void(void)> callbacks[3][350];
	static bool isKeyPressed[350];

	static IDirectInputDevice8 * DIKeyboard;
	static IDirectInputDevice8 * DIMouse;
	static BYTE keyboardState[256];
	static DIMOUSESTATE mouseLastState;
	static DIMOUSESTATE mouseCurrState;
	static LPDIRECTINPUT8 DirectInput;
};

}
#endif
