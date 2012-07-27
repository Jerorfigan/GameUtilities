#include "stdafx.h"

#include <memory>

#include "DirectInput8Keyboard.h"
#include "Globals.h"
#include "DirectInput8InputLayer.h"
#include "UtilityError.h"

namespace GameUtilities
{

	/****************/
	/* Constructors */
	/****************/
	DirectInput8Keyboard::DirectInput8Keyboard( HWND hWnd )
	{
		LPDIRECTINPUT8 pDirectInput = Input()->GetDirectInput();

		// Create the keyboard device interface.
		HRESULT hr = pDirectInput->CreateDevice( GUID_SysKeyboard, &m_pDevice, NULL );
		if( FAILED(hr) )
			throw UtilityError( "[DirectInput8Keyboard::DirectInput8Keyboard]: Failed to create DirectInput8 keyboard device." );

		// Set the keyboard data format.
		hr = m_pDevice->SetDataFormat( &c_dfDIKeyboard ); 
		if( FAILED(hr) )
		{
			SafeRelease( m_pDevice );
			throw UtilityError( "[DirectInput8Keyboard::DirectInput8Keyboard]: Failed to set DirectInput8 keyboard device format." );
		}

		// Set the cooperative level.
		hr = m_pDevice->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE ); 
		if( FAILED(hr) )
		{
			SafeRelease( m_pDevice );
			throw UtilityError( "[DirectInput8Keyboard::DirectInput8Keyboard]: Failed to set DirectInput8 keyboard device cooperative level." );
		}

		memset( m_keyState, 0, sizeof(m_keyState) );
	}

	/***********/
	/* Methods */
	/***********/

	//////////
	// Poll //
	////////// 
	bool DirectInput8Keyboard::Poll( char key )
	{
		// First try to acquire the device. If we can't just return false.
		HRESULT hr = m_pDevice->Acquire();
		if( FAILED(hr) )
			return false;

		// Clear the previous state.
		memset( m_keyState, 0, sizeof( m_keyState ) );

		// Poll and get the new state of the device. If we can't just return false.
		hr = m_pDevice->Poll();
		if( FAILED(hr) )
			return false;
		hr = m_pDevice->GetDeviceState( sizeof(m_keyState), (LPVOID)&m_keyState ); 
		if( FAILED(hr) )
			return false;

		// Test if key is down.
		if( m_keyState[key] & 0x80 )
			return true;
		return false;
	}

	/**************/
	/* Destructor */
	/**************/
	DirectInput8Keyboard::~DirectInput8Keyboard()
	{
		if( m_pDevice )
			m_pDevice->Unacquire();
		SafeRelease( m_pDevice );
	}
}