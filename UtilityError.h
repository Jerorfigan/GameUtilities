#pragma once

/*************************************************/
/*************************************************/
/* Object that holds info about a utility error. */
/*************************************************/
/*************************************************/

/****************/
/* STL includes */
/****************/
#include <string>

/*********************/
/* Homebrew includes */
/*********************/
#include "..\BlackJack\GameError.h"

namespace GameUtilities
{

	class UtilityError : public BlackJack::GameError
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		UtilityError( std::string errorDescription ) : 
			BlackJack::GameError( errorDescription )
		{

		}

	};

}