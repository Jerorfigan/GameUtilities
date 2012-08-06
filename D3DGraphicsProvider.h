#pragma once

/***************************/
/***************************/
/* D3D graphics provider . */
/***************************/
/***************************/

#include <Windows.h>
#include <map>

#include "Globals.h"
#include "IGraphicsProvider.h"
#include "D3DSpriteCollection.h"
#include "D3DSpriteInfo.h"
#include "D3DTextureCache.h"
#include "UtilityError.h"
#include "D3D9GraphicsLayer.h"

namespace GameUtilities
{

	class D3DGraphicsProvider : public IGraphicsProvider
	{
		/************/
		/* Typedefs */
		/************/
	public:
		typedef std::map< SpriteCollectionID, D3DSpriteCollection* > SpriteCollectionMap;

		/****************/
		/* Constructors */
		/****************/
	public:
		D3DGraphicsProvider( HWND hWnd, uint backbufferWidth, uint backbufferHeight );

		/***********/
		/* Methods */
		/***********/
	private:
		void			    VerifySpriteCollectionID( SpriteCollectionID id, bool isPresent = true );
		D3DSpriteInfo       ConstructD3DSpriteInfo( SpriteInfo info );
		SpriteInfo          ExtractSpriteInfo( D3DSpriteInfo D3Dinfo );

		/*******************/
		/* Virtual methods */
		/*******************/
	public:
		/* Backbuffer management */
		virtual void                  BeginScene();
		virtual void                  EndScene();
		virtual void                  ClearBackbuffer();
		virtual void                  Flip();

		/* Sprite management. */
		virtual	SpriteCollectionID    CreateSpriteCollection();
		virtual void				  DestroySpriteCollection( SpriteCollectionID id );
		virtual void				  AddSprite( SpriteCollectionID id, std::string name, const SpriteInfo &info );
		virtual void                  RemoveSprite( SpriteCollectionID id, std::string name );
		virtual void			      SetSprite( SpriteCollectionID id, std::string name, const SpriteInfo &info );
		virtual SpriteInfo		      GetSprite( SpriteCollectionID id, std::string name );
		virtual void				  DrawSpriteCollection( SpriteCollectionID id );
		virtual void				  StartSpriteBatch();
		virtual void				  EndSpriteBatch();

		/**************/
		/* Destructor */
		/**************/
	public:
		~D3DGraphicsProvider();

		/********/
		/* Data */
		/********/
	private:
		 SpriteCollectionMap    m_spriteCollections;
	};

	/***********/
	/* Inlines */
	/***********/

	//////////////////////////////
	// VerifySpriteCollectionID //
	//////////////////////////////
	inline void    
	D3DGraphicsProvider::VerifySpriteCollectionID( SpriteCollectionID id, bool isPresent )
	{
		SpriteCollectionMap::iterator findResult = m_spriteCollections.find( id );
		if( findResult == m_spriteCollections.end() && isPresent )
			throw UtilityError( "[D3DGraphicsProvider::VerifySpriteCollectionID]: Invalid sprite collection ID passed to D3DGraphicsProvider." );
		else if( findResult != m_spriteCollections.end() && !isPresent )
			throw UtilityError( "[D3DGraphicsProvider::VerifySpriteCollectionID]: Collection ID passed to D3DGraphicsProvider already in use." );
	}

	////////////////////////////
	// ConstructD3DSpriteInfo //
	////////////////////////////
	inline D3DSpriteInfo    
	D3DGraphicsProvider::ConstructD3DSpriteInfo( SpriteInfo info )
	{
		D3DSpriteInfo spriteInfo;
		spriteInfo.alpha = info.alpha;
		spriteInfo.center = info.center;
		spriteInfo.imageFile = info.imageFile;
		spriteInfo.position = info.position;
		spriteInfo.rotation = info.rotation;
		spriteInfo.scaleX = info.scaleX;
		spriteInfo.scaleY = info.scaleY;
		spriteInfo.subrect = info.subrect;
		spriteInfo.zDepth = info.zDepth;

		return spriteInfo;
	}

	///////////////////////
	// ExtractSpriteInfo //
	///////////////////////
	inline D3DGraphicsProvider::SpriteInfo       
	D3DGraphicsProvider::ExtractSpriteInfo( D3DSpriteInfo info )
	{
		SpriteInfo spriteInfo;
		spriteInfo.alpha = info.alpha;
		spriteInfo.center = info.center;
		spriteInfo.imageFile = info.imageFile;
		spriteInfo.position = info.position;
		spriteInfo.rotation = info.rotation;
		spriteInfo.scaleX = info.scaleX;
		spriteInfo.scaleY = info.scaleY;
		spriteInfo.subrect = info.subrect;
		spriteInfo.zDepth = info.zDepth;

		return spriteInfo;
	}

	////////////////
	// BeginScene //
	////////////////
	inline void                  
	D3DGraphicsProvider::BeginScene()
	{
		Graphics()->GetD3DDevice()->BeginScene();
	}

	inline void                  
	D3DGraphicsProvider::EndScene()
	{
		Graphics()->GetD3DDevice()->EndScene();
	}

	/////////////////////
	// ClearBackbuffer //
	/////////////////////
	inline void 
	D3DGraphicsProvider::ClearBackbuffer()
	{
		Graphics()->GetD3DDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB( 255, 255, 255, 255 ), 1, 0 ); 
	}

	//////////
	// Flip //
	//////////
	inline void                  
	D3DGraphicsProvider::Flip()
	{
		Graphics()->Flip();
	}
}