#pragma once

#ifndef _KEY_EVENT_HANDLER_H_
#define _KEY_EVENT_HANDLER_H_

#include <Windows.h>

namespace core {
	class KeyEventHandler
	{
	public:
		virtual void KeyState(BYTE* state) = 0;
		virtual void OnKeyDown(int key_code) = 0;
		virtual void OnKeyUp(int key_code) = 0;
	};

	typedef KeyEventHandler* LPKEYEVENTHANDLER;
}

#endif // !_KEY_EVENT_HANDLER_H
