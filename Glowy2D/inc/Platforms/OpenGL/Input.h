/****************************************************************************
This file is part of glowy2d.

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
#ifdef R_OGL
#include <functional>

struct GLFWwindow;

namespace glowy2d
{

class Input
{
public:
	enum PressType : ubyte
	{
		release,
		press,
		hold
	};
	
	enum Keyboard
	{
		unknown = -1,
		a = 65,
		b,
		c,
		d,
		e,
		f,
		g,
		h,
		i,
		j,
		k,
		l,
		m,
		n,
		o,
		p,
		q,
		r,
		s,
		t,
		u,
		v,
		w,
		x,
		y,
		z,
		space = 32,
		apostrophe = 39, //'
		comma = 44, //,
		minus = 45, //-
		period = 46,//.
		slash = 46, ///
		num0 = 48,
		num1,
		num2,
		num3,
		num4,
		num5,
		num6,
		num7,
		num8,
		num9,
		semicolon = 59,//;
		equal = 61, // =
		bracketl = 91, //[
		backslash = 92,
		bracketr,
		grave = 96, //`
		world1 = 161,
		world2,
		escape = 256,
		enter,
		tab,
		backspace,
		insert,
		del,
		right,
		left,
		down,
		up,
		pageup,
		pagedown,
		home,
		end,
		capslock = 280,
		scrolllock,
		numlock,
		printscreen,
		pause,
		F1 = 290,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		F16,
		F17,
		F18,
		F19,
		F20,
		F21,
		F22,
		F23,
		F24,
		F25,
		numpad0 = 320,
		numpad1,
		numpad2,
		numpad3,
		numpad4,
		numpad5,
		numpad6,
		numpad7,
		numpad8,
		numpad9,
		numpadDecimal,
		numpadDivide,
		numpadMultiply,
		numpadSubstract,
		numpadAdd,
		numpadEnter,
		numpadEqual,
		lshift = 340,
		lctrl,
		lalt,
		lsuper,
		rshift,
		rctrl,
		ralt,
		rsuper,
		menu,
		last = 348,
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

	friend void callbackFunction(GLFWwindow * window, int key, int scancode, int action, int mods);

private:
	Input() {}
	~Input() {}

	//thread-unsafe?
	static std::function<void(void)> callbacks[3][350];
	static bool isKeyPressed[350];
};

}
#endif