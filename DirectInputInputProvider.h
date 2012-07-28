#pragma once

/******************************************/
/******************************************/
/* Interface to DirectInput input system. */
/******************************************/
/******************************************/

#include <Windows.h>

#include "IRealTimeInputProvider.h"
#include "DirectInput8InputLayer.h"

namespace GameUtilities
{

	class DirectInputInputProvider : public IRealTimeInputProvider
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		DirectInputInputProvider( HINSTANCE hInst, HWND hWnd, bool exclusive );

		/*******************/
		/* Virtual methods */
		/*******************/
	public:
		virtual bool IsKeyDown( char key );
		virtual bool IsKeyDown( UINT winVirtualKey );

		/**************/
		/* Destructor */
		/**************/
	public:
		~DirectInputInputProvider();
	};

	/***********/
	/* Inlines */
	/***********/

	///////////////////////////
	// IsKeyDown( char key ) //
	///////////////////////////
	inline bool 
	DirectInputInputProvider::IsKeyDown( char key )
	{
		UINT VKCode = LOBYTE( VkKeyScan( key ) );
		UINT scanCode = MapVirtualKey( VKCode, 0 );
		return Input()->GetKeyboard()->Poll( scanCode );
	}

	/////////////////////////////////////
	// IsKeyDown( UINT winVirtualKey ) //
	/////////////////////////////////////
	inline bool 
	DirectInputInputProvider::IsKeyDown( UINT winVirtualKey )
	{
		UINT scanCode = MapVirtualKey( winVirtualKey, 0 );
		return Input()->GetKeyboard()->Poll( scanCode );
	}
}