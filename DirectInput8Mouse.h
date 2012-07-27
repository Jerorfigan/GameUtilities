#pragma once

/****************************************/
/****************************************/
/* Wraps the DirectInput8 mouse device. */
/****************************************/
/****************************************/

#include <Windows.h>
#include <dinput.h>

namespace GameUtilities
{

	class DirectInput8Mouse
	{
		/********************/
		/* Internal classes */
		/********************/
	public:
		struct IMouseReceiver
		{
			virtual void MouseMoved( int dx, int dy ) = 0;
			virtual void MouseButtonUp( int button ) = 0;
			virtual void MouseButtonDown( int button ) = 0;
			virtual ~IMouseReceiver() {};
		};

		/****************/
		/* Constructors */
		/****************/
	public:
		DirectInput8Mouse( HWND hWnd, bool exclusive );

		/***********/
		/* Methods */
		/***********/
	public:
		void SetReceiver( IMouseReceiver *pMouseReceiver );
		void Update();
		void Acquire();
		void Unacquire();

		/**************/
		/* Destructor */
		/**************/
	public:
		~DirectInput8Mouse();

		/********/
		/* Data */
		/********/
	private:
		LPDIRECTINPUTDEVICE8    m_pDevice;
		DIMOUSESTATE			m_lastState;
		IMouseReceiver			*m_pMouseReceiver;
	};

}