#pragma once

/*******************************************/
/*******************************************/
/* Wraps the DirectInput8 keyboard device. */
/*******************************************/
/*******************************************/

#include <Windows.h>
#include <dinput.h>

namespace GameUtilities
{

	class DirectInput8Keyboard
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		DirectInput8Keyboard( HWND hWnd );

		/***********/
		/* Methods */
		/***********/
	public:
		bool    Poll( int key );

		/**************/
		/* Destructor */
		/**************/
	public:
		~DirectInput8Keyboard();

		/********/
		/* Data */
		/********/
	private:
		LPDIRECTINPUTDEVICE8    m_pDevice;
		char					m_keyState[256];
	};

}