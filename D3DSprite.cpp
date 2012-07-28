#include "stdafx.h"

#include <d3dx9.h>
#include <Windows.h>

#include "D3DSprite.h"
#include "D3DTextureCache.h"
#include "Globals.h"
#include "D3D9GraphicsLayer.h"
#include "UtilityError.h"

namespace GameUtilities
{

	/****************/
	/* Constructors */
	/****************/
	D3DSprite::D3DSprite( const D3DSpriteInfo &info ) : 
		m_info( info )
	{
		// Load the texture that this sprite utilizes in advance of drawing it.
		TextureCache()->GetTexture( m_info.imageFile, m_ID );
	}

	/***********/
	/* Methods */
	/***********/
	void		     
	D3DSprite::Draw() const
	{
		// Construct and set the world transformation matrix.
		D3DXMATRIX world, rotation, scale, translation;
		D3DXMatrixRotationYawPitchRoll( &rotation, 0, 0, m_info.rotation * PI / 180.0f );
		D3DXMatrixScaling( &scale, m_info.scale, m_info.scale, 0 );
		D3DXMatrixTranslation( &translation, m_info.position.x, m_info.position.y, 0 );
		world = rotation * scale * translation;
		
		Graphics()->GetSpriteInterface()->SetTransform( &world );

		// Construct the subrect pointer.
		const RECT *pRect = m_info.subrect.right == m_info.subrect.left || 
			m_info.subrect.top == m_info.subrect.bottom ? NULL : &m_info.subrect;

		// Construct the texture center vector.
		D3DXVECTOR3 center;
		center.x = m_info.center.x;
		center.y = m_info.center.y;
		center.z = 0;

		// Construct the alpha value.
		BYTE alphaValue = static_cast< BYTE >( 255 * m_info.alpha );

		HRESULT hr = Graphics()->GetSpriteInterface()->Draw( 
			TextureCache()->GetTexture( m_info.imageFile, m_ID ), 
			pRect, 
			&center, 
			NULL, 
			D3DCOLOR_RGBA( 255, 255, 255, alphaValue ) );
		
		if( FAILED(hr) ) 
			throw UtilityError( "[D3DSprite::Draw]: Call to ID3DXSprite::Draw failed to draw the sprite." );
	}

	/**************/
	/* Destructor */
	/**************/
	D3DSprite::~D3DSprite()
	{
		// Release the texture that this sprite was referecing. If no other
		// sprites are referencing it, the texture cache will free it from
		// memory.
		TextureCache()->ReleaseTexture( m_info.imageFile, m_ID );
	}

}