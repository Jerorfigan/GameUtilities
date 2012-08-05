#pragma once

/**********************************************************/
/**********************************************************/
/* Holds a collection of sprites tied to a collection ID. */
/**********************************************************/
/**********************************************************/

#include <map>

#include "D3DSprite.h"
#include "UtilityError.h"
#include "D3DSpriteDrawQueue.h"

namespace GameUtilities
{

	class D3DSpriteCollection
	{
		/************/
		/* Typedefs */
		/************/
	public:
		typedef std::size_t ID;
		typedef std::map< D3DSprite::Name, D3DSprite* > SpriteMap;

		/***************/
		/* Constructor */
		/***************/
	public:
		D3DSpriteCollection() : m_ID( m_IDSequence++ ) {}

		/***********/
		/* Methods */
		/***********/
	public:
		void		  DrawCollection();
		void		  AddSprite( D3DSprite::Name name, D3DSprite* sprite );
		void		  RemoveSprite( D3DSprite::Name name );
		D3DSprite*    GetSprite( D3DSprite::Name name );
		ID			  GetID();

	private:
		void		  VerifySpriteName( D3DSprite::Name name, bool isPresent = true ); 

		/**************/
		/* Destructor */
		/**************/
	public:
		~D3DSpriteCollection();

		/********/
		/* Data */
		/********/
	private:
		SpriteMap    m_sprites; 
		ID			 m_ID;

		/***************/
		/* Static data */
		/***************/
	private:
		static ID    m_IDSequence;
	};

	/***********/
	/* Inlines */
	/***********/

	////////////////////
	// DrawCollection //
	////////////////////
	inline void		  
	D3DSpriteCollection::DrawCollection()
	{
		for( SpriteMap::iterator spriteItr = m_sprites.begin();
			 spriteItr != m_sprites.end(); ++spriteItr )
		{
			SpriteDrawQueue()->AddToDrawQueue( spriteItr->second );
		}
	}
	
	///////////////
	// AddSprite //
	///////////////
	inline void		  
	D3DSpriteCollection::AddSprite( D3DSprite::Name name, D3DSprite* sprite )
	{
		VerifySpriteName( name, false );
		m_sprites[ name ] = sprite;
	}
	
	inline void		  
	D3DSpriteCollection::RemoveSprite( D3DSprite::Name name )
	{
		VerifySpriteName( name );
		m_sprites.erase( name );
	}
	
	inline D3DSprite*    
	D3DSpriteCollection::GetSprite( D3DSprite::Name name )
	{
		VerifySpriteName( name );
		return m_sprites[ name ];
	}

	///////////
	// GetID //
	///////////
	inline D3DSpriteCollection::ID			  
	D3DSpriteCollection::GetID()
	{
		return m_ID;
	}

	//////////////////////
	// VerifySpriteName //
	//////////////////////
	inline void		  
	D3DSpriteCollection::VerifySpriteName( D3DSprite::Name name, bool isPresent )
	{
		SpriteMap::iterator findResult = m_sprites.find( name );
		if( findResult == m_sprites.end() && isPresent )
			throw UtilityError( "[D3DSpriteCollection::VerifySpriteName]: Invalid sprite name passed to D3DGraphicsProvider." );
		else if( findResult != m_sprites.end() && !isPresent )
			throw UtilityError( "[D3DSpriteCollection::VerifySpriteName]: Sprite name passed to D3DGraphicsProvider already in use." );
	}

	////////////////
	// Destructor //
	////////////////
	inline D3DSpriteCollection::~D3DSpriteCollection()
	{
		// De-allocate sprites.
		for( SpriteMap::iterator spriteItr = m_sprites.begin();
			 spriteItr != m_sprites.end(); ++spriteItr )
		{
			delete spriteItr->second;
		}
	}

}