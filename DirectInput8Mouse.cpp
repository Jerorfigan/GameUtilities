#include "stdafx.h"

#include "DirectInput8Mouse.h"
#include "DirectInput8InputLayer.h"
#include "UtilityError.h"
#include "Globals.h"

namespace GameUtilities
{

		/****************/
		/* Constructors */
		/****************/
		DirectInput8Mouse::DirectInput8Mouse( HWND hWnd, bool exclusive ) :
			m_pMouseReceiver( NULL )
		{
			LPDIRECTINPUT8 pDirectInput = Input()->GetDirectInput();

			// Create the mouse device interface.
			HRESULT hr = pDirectInput->CreateDevice( GUID_SysMouse, &m_pDevice, NULL );
			if( FAILED(hr) )
				throw UtilityError( "[DirectInput8Mouse::DirectInput8Mouse]: Failed to create DirectInput8 mouse device." );

			// Set the data format.
			hr = m_pDevice->SetDataFormat( &c_dfDIMouse );
			if( FAILED(hr) )
			{
				SafeRelease( m_pDevice );
				throw UtilityError( "[DirectInput8Mouse::DirectInput8Mouse]: Failed to set DirectInput8 mouse device format." );
			}

			// Set the cooperative level.
			if( exclusive )
			{
				hr = m_pDevice->SetCooperativeLevel( hWnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND );
			}
			else
			{
				hr = m_pDevice->SetCooperativeLevel( hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
			}
			if( FAILED(hr) )
			{
				SafeRelease( m_pDevice );
				throw UtilityError( "[DirectInput8Mouse::DirectInput8Mouse]: Failed to set DirectInput8 mouse device cooperative level." );
			}

			m_lastState.lX = 0;
			m_lastState.lY = 0;
			m_lastState.lZ = 0;
			m_lastState.rgbButtons[0] = 0;
			m_lastState.rgbButtons[1] = 0;
			m_lastState.rgbButtons[2] = 0;
			m_lastState.rgbButtons[3] = 0;
		}

		/***********/
		/* Methods */
		/***********/
		
		/////////////////
		// SetReceiver //
		/////////////////
		void 
		DirectInput8Mouse::SetReceiver( IMouseReceiver *pMouseReceiver )
		{
			m_pMouseReceiver = pMouseReceiver;
		}

		////////////
		// Update //
		////////////
		void 
		DirectInput8Mouse::Update()
		{
			DIMOUSESTATE currState;
			HRESULT hr;

			hr = m_pDevice->Acquire();
			if( FAILED(hr) )
				return;
			hr = m_pDevice->Poll(); 
			if( FAILED(hr ) )
				return;
			hr = m_pDevice->GetDeviceState( sizeof(DIMOUSESTATE), (void*)&currState );
			if( FAILED(hr) )
				return;

			if( m_pMouseReceiver )
			{
				int dx = currState.lX;
				int dy = currState.lY;
				if( dx || dy )
				{
					m_pMouseReceiver->MouseMoved( dx, dy );
				}
				if( currState.rgbButtons[0] & 0x80 )
				{
					// the button got pressed.
					m_pMouseReceiver->MouseButtonDown( 0 );
				}
				if( currState.rgbButtons[1] & 0x80 )
				{
					// the button got pressed.
					m_pMouseReceiver->MouseButtonDown( 1 );
				}
				if( currState.rgbButtons[2] & 0x80 )
				{
					// the button got pressed.
					m_pMouseReceiver->MouseButtonDown( 2 );
				}
				if( !(currState.rgbButtons[0] & 0x80) && (m_lastState.rgbButtons[0] & 0x80) )
				{
					// the button got released.
					m_pMouseReceiver->MouseButtonUp( 0 );
				}
				if( !(currState.rgbButtons[1] & 0x80) && (m_lastState.rgbButtons[1] & 0x80) )
				{
					// the button got released.
					m_pMouseReceiver->MouseButtonUp( 1 );
				}
				if( !(currState.rgbButtons[2] & 0x80) && (m_lastState.rgbButtons[2] & 0x80) )
				{
					// the button got released.
					m_pMouseReceiver->MouseButtonUp( 2 );
				}
			}
			m_lastState = currState;
		}

		/////////////
		// Acquire //
		/////////////
		void 
		DirectInput8Mouse::Acquire()
		{
			m_pDevice->Acquire();
		}

		///////////////
		// Unacquire //
		///////////////
		void 
		DirectInput8Mouse::Unacquire()
		{
			m_pDevice->Unacquire();
		}

		/**************/
		/* Destructor */
		/**************/
		DirectInput8Mouse::~DirectInput8Mouse()
		{
			if( m_pDevice )
				m_pDevice->Unacquire();
			SafeRelease( m_pDevice );
		}

}