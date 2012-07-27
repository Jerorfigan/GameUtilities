#pragma once

/*****************/
/*****************/
/* Global stuff. */
/*****************/
/*****************/

namespace GameUtilities
{

	/************/
	/* Typedefs */
	/************/
	typedef unsigned int uint;

	/********************/
	/* Global variables */
	/********************/
	#ifdef GLOBAL_DEF
	float PI = 3.14f;
	#else
	extern float PI;
	#endif

	/****************************************************/
	/* Template function to release COM objects safely. */
	/****************************************************/
	template < typename COMTypePtr >
	void SafeRelease( COMTypePtr &comPtr )
	{
		if( comPtr )
		{
			comPtr->Release();
			comPtr = NULL;
		}
	}

}