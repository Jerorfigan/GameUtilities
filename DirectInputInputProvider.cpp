#include "stdafx.h"

#include "DirectInputInputProvider.h"

namespace GameUtilities
{

	/****************/
	/* Constructors */
	/****************/
	DirectInputInputProvider::DirectInputInputProvider( HINSTANCE hInst, HWND hWnd, bool exclusive )
	{
		// Create DirectInput8 input layer.
		DirectInput8InputLayer::Create( hInst, hWnd, exclusive );

		// Populate the scan code map.
		// RightArrow, LeftArrow, UpArrow, DownArrow
		m_scanCodes[ RightArrow ] = DIK_RIGHT;
		m_scanCodes[ LeftArrow ] = DIK_LEFT;
		m_scanCodes[ UpArrow ] = DIK_UP;
		m_scanCodes[ DownArrow ] = DIK_DOWN;
	}

	/**************/
	/* Destructor */
	/**************/
	DirectInputInputProvider::~DirectInputInputProvider()
	{
		// Free DirectInput8 input layer.
		DirectInput8InputLayer::Destroy();
	}

}