#pragma once

/******************************************************/
/******************************************************/
/* Wrapper for class for manipulating sprites in D3D. */
/******************************************************/
/******************************************************/

#include <cstddef>

#include "D3DSpriteInfo.h"

namespace GameUtilities
{

	struct D3DSprite
	{
		/************/
		/* Typedefs */
		/************/
	public:
		typedef std::size_t ID;
		typedef std::string Name;

		/****************/
		/* Constructors */
		/****************/
	public:
		D3DSprite( const D3DSpriteInfo &info );

		/***********/
		/* Methods */
		/***********/
	public:
		void		     Draw() const;
		void			 Set( const D3DSpriteInfo &info );
		D3DSpriteInfo    Get();

		/**************/
		/* Destructor */
		/**************/
	public:
		~D3DSprite();

		/*********/
		/* Data  */
		/*********/
	public:
		D3DSpriteInfo		   m_info;
		ID                     m_ID;

		/***************/
		/* Static data */
		/***************/
	private:
		static ID    m_IDSequence;
	};

	/***********/
	/* Inlines */
	/***********/

	/////////
	// Set //
	/////////
	inline void			 
	D3DSprite::Set( const D3DSpriteInfo &info )
	{
		m_info = info;
	}

	/////////
	// Get //
	/////////
	inline D3DSpriteInfo    
	D3DSprite::Get()
	{
		return m_info;
	}
}