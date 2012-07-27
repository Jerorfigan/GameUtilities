#pragma once

/******************************************************/
/******************************************************/
/* Manages the retrieval/caching of all D3D textures. */
/******************************************************/
/******************************************************/

#include <d3d9.h>
#include <map>
#include <string>

#include "D3DTexture.h"

namespace GameUtilities
{

	class D3DTextureCache
	{
		/************/
		/* Typedefs */
		/************/
	public:
		typedef std::map< std::string, D3DTexture* > TextureMap;

		/****************/
		/* Constructors */
		/****************/
	public:
		D3DTextureCache();

		/***********/
		/* Methods */
		/***********/
	public:
		LPDIRECT3DTEXTURE9    GetTexture( std::string imageFile, D3DSprite::ID spriteID );
		void				  ReleaseTexture( std::string imageFile, D3DSprite::ID spriteID );

	private:
		bool TextureLoaded( std::string imageFile );

		/********/
		/* Data */
		/********/
	public:
		TextureMap m_textures;

		/******************/
		/* Static methods */
		/******************/
	public:
		static void Create();
		static void Destroy();
		static D3DTextureCache* GetTextureCache();

		/***************/
		/* Static data */
		/***************/
	public:
		static D3DTextureCache *m_pD3DTextureCache;
	};

	/***********/
	/* Inlines */
	/***********/

	///////////////////
	// TextureLoaded //
	///////////////////
	inline bool 
	D3DTextureCache::TextureLoaded( std::string imageFile )
	{
		TextureMap::iterator findResult = m_textures.find( imageFile );
		return findResult != m_textures.end();
	}

	/******************/
	/* Static inlines */
	/******************/
	
	////////////
	// Create //
	////////////
	inline void 
	D3DTextureCache::Create()
	{
		new D3DTextureCache();
	}

	/////////////
	// Destroy //
	/////////////
	inline void 
	D3DTextureCache::Destroy()
	{
		delete m_pD3DTextureCache;
		m_pD3DTextureCache = NULL;
	}
	
	/////////////////////
	// GetTextureCache //
	/////////////////////
	inline D3DTextureCache* 
	D3DTextureCache::GetTextureCache()
	{
		return m_pD3DTextureCache;
	}

	/*******************************************************************/
	/* Global abbreviated wrapper for D3DTextureCache::GetTextureCache */
	/*******************************************************************/
	inline D3DTextureCache*
	TextureCache()
	{
		return D3DTextureCache::GetTextureCache();
	}

}