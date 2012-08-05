#include "stdafx.h"

#include <d3dx9.h>

#include "D3DTextureCache.h"
#include "UtilityError.h"
#include "D3D9GraphicsLayer.h"

namespace GameUtilities
{

	/****************/
	/* Constructors */
	/****************/
	D3DTextureCache::D3DTextureCache()
	{
		if( m_pD3DTextureCache )
		{
			throw UtilityError( "[D3DTextureCache::D3DTextureCache]: Attempt to create multiple instances of singleton class D3DTextureCache." );
		}

		m_pD3DTextureCache = this;
	}

	/***********/
	/* Methods */
	/***********/

	////////////////
	// GetTexture //
	////////////////
	LPDIRECT3DTEXTURE9    
	D3DTextureCache::GetTexture( std::string imageFile, D3DSprite::ID spriteID )
	{
		if( !TextureLoaded( imageFile ) )
		{
			D3DTexture *pTexture = new D3DTexture();
			HRESULT hr = D3DXCreateTextureFromFile( Graphics()->GetD3DDevice(), imageFile.c_str(), &pTexture->m_pD3DTexture9 );
			if( FAILED(hr) )
				throw UtilityError( "[D3DTextureCache::GetTexture]: D3DXCreateTextureFromFile failed to load texture." );
			m_textures[ imageFile ] = pTexture;
		}

		m_textures[ imageFile ]->m_refSprites.insert( spriteID );

		return m_textures[ imageFile ]->m_pD3DTexture9;
	}

	////////////////////
	// ReleaseTexture //
	////////////////////
	void				  
	D3DTextureCache::ReleaseTexture( std::string imageFile, D3DSprite::ID spriteID )
	{
		if( !TextureLoaded( imageFile ) )
			throw UtilityError( "[D3DTextureCache::ReleaseTexture]: ReleaseTexture called on a texture that was already released." );

		// Erase spriteID (the ID of the sprite calling release) from the set of referecing sprites stored in the D3DTexture.
		m_textures[ imageFile ]->m_refSprites.erase( spriteID );

		// Release D3D texture if no more sprites are referencing it.
		if( m_textures[ imageFile ]->m_refSprites.size() == 0 )
		{
			m_textures[ imageFile ]->m_pD3DTexture9->Release();
			m_textures.erase( imageFile );
		}
	}

	/***************/
	/* Static data */
	/***************/
	D3DTextureCache *D3DTextureCache::m_pD3DTextureCache = NULL;

}