#pragma once

/***********************************************/
/***********************************************/
/* Manages the DirectInput8 interface objects. */
/***********************************************/
/***********************************************/

#include <Windows.h>
#include <dinput.h>

#include "DirectInput8Keyboard.h"
#include "DirectInput8Mouse.h"

namespace GameUtilities
{
	class DirectInput8InputLayer
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		DirectInput8InputLayer( HINSTANCE hInst, HWND hWnd, bool exclusive, bool useKeyboard = true, bool useMouse = true ); 

		/***********/
		/* Methods */
		/***********/
	public:
		DirectInput8Keyboard*    GetKeyboard();
		DirectInput8Mouse*       GetMouse();
		LPDIRECTINPUT8		     GetDirectInput();
		void				     SetFocus();
		void				     KillFocus();

		/**************/
		/* Destructor */
		/**************/
	public:
		~DirectInput8InputLayer();

		/********/
		/* Data */
		/********/
	private:
		LPDIRECTINPUT8           m_pDirectInput8;
		DirectInput8Keyboard    *m_pKeyboard;
		DirectInput8Mouse       *m_pMouse;

		/******************/
		/* Static methods */
		/******************/
	public:
		static void						  Create( HINSTANCE hInst, HWND hWnd, bool exclusive, bool useKeyboard = true, bool useMouse = true );
		static void						  Destroy();
		static DirectInput8InputLayer*    GetInputLayer();

		/***************/
		/* Static data */
		/***************/
	private:
		static DirectInput8InputLayer *m_pD3D8InputLayer;
	};

	/***********/
	/* Inlines */
	/***********/

	/////////////////
	// GetKeyboard //
	/////////////////
	inline DirectInput8Keyboard*    
	DirectInput8InputLayer::GetKeyboard()
	{
		return m_pKeyboard;
	}
	
	//////////////
	// GetMouse //
	//////////////
	inline DirectInput8Mouse*       
	DirectInput8InputLayer::GetMouse()
	{
		return m_pMouse;
	}

	////////////////////
	// GetDirectInput //
	////////////////////
	inline LPDIRECTINPUT8
	DirectInput8InputLayer::GetDirectInput()
	{
		return m_pDirectInput8;
	}

	/******************/
	/* Static inlines */
	/******************/

	///////////////////
	// GetInputLayer //
	///////////////////
	inline DirectInput8InputLayer* 
	DirectInput8InputLayer::GetInputLayer()
	{
		return m_pD3D8InputLayer;
	}

	/*************************************************************************/
	/* Global abbreviated wrapper for DirectInput8InputLayer::GetInputLayer. */
	/*************************************************************************/
	inline DirectInput8InputLayer* 
	Input()
	{
		return DirectInput8InputLayer::GetInputLayer();
	}

}