#pragma once

/******************************************/
/******************************************/
/* Interface to DirectInput input system. */
/******************************************/
/******************************************/

#include <Windows.h>
#include <map>

#include "IRealTimeInputProvider.h"
#include "DirectInput8InputLayer.h"

namespace GameUtilities
{

	class DirectInputInputProvider : public IRealTimeInputProvider
	{
		/************/
		/* Typedefs */
		/************/
	private:
		typedef std::map< NonCharKey, UINT > ScanCodeMap;

		/****************/
		/* Constructors */
		/****************/
	public:
		DirectInputInputProvider( HINSTANCE hInst, HWND hWnd, bool exclusive );

		/*******************/
		/* Virtual methods */
		/*******************/
	public:
		virtual bool    IsKeyDown( char key );
		virtual bool    IsKeyDown( NonCharKey key );

		/**************/
		/* Destructor */
		/**************/
	public:
		~DirectInputInputProvider();

		/********/
		/* Data */
		/********/
	private:
		ScanCodeMap    m_scanCodes;
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

	/////////////////////////////////
	// IsKeyDown( NonCharKey key ) //
	/////////////////////////////////
	inline bool 
	DirectInputInputProvider::IsKeyDown( NonCharKey key )
	{
		// Translate the non-char key enum to its appropriate scan code via the 
		// lookup table.
		if( m_scanCodes.find( key ) != m_scanCodes.end() )
			return Input()->GetKeyboard()->Poll( m_scanCodes[ key ] );
		return false;
	}
}