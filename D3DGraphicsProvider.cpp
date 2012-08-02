#include "stdafx.h"

#include "D3DGraphicsProvider.h"
#include "D3DSpriteInfo.h"
#include "D3DSprite.h"
#include "D3DTextureCache.h"
#include "D3DSpriteDrawQueue.h"

namespace GameUtilities
{

	/****************/
	/* Constructors */
	/****************/
	D3DGraphicsProvider::D3DGraphicsProvider( HWND hWnd, uint backbufferWidth, uint backbufferHeight )
	{
		D3D9GraphicsLayer::Create( hWnd, backbufferWidth, backbufferHeight, NULL, false );
		D3DTextureCache::Create();
		D3DSpriteDrawQueue::Create();
	}

	/*******************/
	/* Virtual methods */
	/*******************/

	///////////////////////
	// Sprite management //
	///////////////////////

	////////////////////////////
	// CreateSpriteCollection //
	////////////////////////////
	D3DGraphicsProvider::SpriteCollectionID    
	D3DGraphicsProvider::CreateSpriteCollection()
	{
		D3DSpriteCollection *pSpriteCollection = new D3DSpriteCollection();
		m_spriteCollections[ pSpriteCollection->GetID() ] = pSpriteCollection;

		return pSpriteCollection->GetID();
	}

	/////////////////////////////
	// DestroySpriteCollection //
	/////////////////////////////
	void				
	D3DGraphicsProvider::DestroySpriteCollection( SpriteCollectionID id )
	{
		VerifySpriteCollectionID( id );
		m_spriteCollections.erase( id );
	}

	///////////////
	// AddSprite //
	///////////////
	void				  
	D3DGraphicsProvider::AddSprite( SpriteCollectionID id, std::string name, const SpriteInfo &info )
	{
		VerifySpriteCollectionID( id );
		D3DSpriteInfo spriteInfo = ConstructD3DSpriteInfo( info );
		D3DSprite *pSprite = new D3DSprite( spriteInfo );
		m_spriteCollections[ id ]->AddSprite( name, pSprite );
	}

	//////////////////
	// RemoveSprite //
	//////////////////
	void                  
	D3DGraphicsProvider::RemoveSprite( SpriteCollectionID id, std::string name )
	{
		VerifySpriteCollectionID( id );
		m_spriteCollections[ id ]->RemoveSprite( name );
	}

	///////////////
	// SetSprite //
	///////////////
	void			      
	D3DGraphicsProvider::SetSprite( SpriteCollectionID id, std::string name, const SpriteInfo &info )
	{
		VerifySpriteCollectionID( id );
		D3DSpriteInfo D3DInfo = ConstructD3DSpriteInfo( info );
		m_spriteCollections[ id ]->GetSprite( name )->Set( D3DInfo );
	}

	///////////////
	// GetSprite //
	///////////////
	D3DGraphicsProvider::SpriteInfo		      
	D3DGraphicsProvider::GetSprite( SpriteCollectionID id, std::string name )
	{
		VerifySpriteCollectionID( id );
		D3DSpriteInfo D3DInfo = m_spriteCollections[ id ]->GetSprite( name )->Get();

		return ExtractSpriteInfo( D3DInfo );
	}

	//////////////////////////
	// DrawSpriteCollection //
	//////////////////////////
	void				  
	D3DGraphicsProvider::DrawSpriteCollection( SpriteCollectionID id )
	{
		VerifySpriteCollectionID( id );
		m_spriteCollections[ id ]->DrawCollection();
	}

	//////////////////////
	// StartSpriteBatch //
	//////////////////////
	void				  
	D3DGraphicsProvider::StartSpriteBatch()
	{
		Graphics()->GetSpriteInterface()->Begin( D3DXSPRITE_ALPHABLEND );
	}

	////////////////////
	// EndSpriteBatch //
	////////////////////
	void				 
	D3DGraphicsProvider::EndSpriteBatch()
	{
		// All sprites to be drawn are sititng in the D3DSpriteDrawQueue, in order of z-depth.
		// So go ahead and draw them now.
		SpriteDrawQueue()->Draw();

		Graphics()->GetSpriteInterface()->End();
	}

	/**************/
	/* Destructor */
	/**************/
	D3DGraphicsProvider::~D3DGraphicsProvider()
	{
		// De-allocate sprite collections.
		for( SpriteCollectionMap::iterator spriteCollectionItr = m_spriteCollections.begin();
			 spriteCollectionItr != m_spriteCollections.end(); ++spriteCollectionItr )
		{
			delete spriteCollectionItr->second;
		}

		// Destroy graphics layer.
		Graphics()->Destroy();
	}
}