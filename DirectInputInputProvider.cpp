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