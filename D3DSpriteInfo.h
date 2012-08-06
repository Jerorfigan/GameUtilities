#pragma once

/*******************************************/
/*******************************************/
/* Used to pass around sprite information. */
/*******************************************/
/*******************************************/

#include <Windows.h>
#include <string>

#include "Point2D.h"

namespace GameUtilities
{

	struct D3DSpriteInfo
	{
		std::string    imageFile;
		RECT		   subrect;
		Point2D		   center;
		Point2D		   position;
		float		   rotation;
		float          scaleX;
		float          scaleY;
		float          alpha;
		float          zDepth;
	};

}