#include "stdafx.h"

#include "DirectInput8InputLayer.h"
#include "UtilityError.h"
#include "Globals.h"

namespace GameUtilities
{

		/****************/
		/* Constructors */
		/****************/
		DirectInput8InputLayer::DirectInput8InputLayer( HINSTANCE hInst, HWND hWnd, bool exclusive, bool useKeyboard, bool useMouse ) :
			m_pKeyboard( NULL ),
			m_pMouse( NULL )
		{
			if( m_pD3D8InputLayer )
				throw UtilityError( "[DirectInput8InputLayer::DirectInput8InputLayer]: Attempt to instantiate multiple instances of " 
								    "singleton class DirectInput8InputLayer." );

			m_pD3D8InputLayer = this;

			// Create the DirectInput8 interface.
			HRESULT hr = DirectInput8Create( hInst, DIRECTINPUT_VERSION, 
				IID_IDirectInput8, (void**)&m_pDirectInput8, NULL );
			if( FAILED(hr) )
				throw UtilityError( "[DirectInput8InputLayer::DirectInput8InputLayer]: Failed to create IDirectInput8 interface." );

			// Create the keyboard/mouse interface objects if requested.
			if( useKeyboard )
			{
				m_pKeyboard = new DirectInput8Keyboard( hWnd );
			}
			if( useMouse )
			{
				m_pMouse = new DirectInput8Mouse( hWnd, exclusive );
			}
		}

		/***********/
		/* Methods */
		/***********/

		//////////////
		// SetFocus //
		//////////////
		void				     
		DirectInput8InputLayer::SetFocus()
		{
			m_pMouse->Acquire();
		}

		///////////////
		// KillFocus //
		///////////////
		void				     
		DirectInput8InputLayer::KillFocus()
		{
			m_pMouse->Unacquire();
		}

		/**************/
		/* Destructor */
		/**************/
		DirectInput8InputLayer::~DirectInput8InputLayer()
		{
			delete m_pKeyboard;
			delete m_pMouse;
			SafeRelease( m_pDirectInput8 );
		}

}