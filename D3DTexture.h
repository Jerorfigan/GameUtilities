#pragma once

/**************************************************/
/**************************************************/
/* Does referencing counting for the D3D texture. */
/**************************************************/
/**************************************************/

#include <d3d9.h>
#include <set>

#include "D3DSprite.h"

namespace GameUtilities
{

	struct D3DTexture
	{
		LPDIRECT3DTEXTURE9			  m_pD3DTexture9;
		std::set< D3DSprite::ID >     m_refSprites;
	};

}