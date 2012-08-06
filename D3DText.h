#pragma once

/********************************************/
/********************************************/
/* A D3D text object that can display text. */
/********************************************/
/********************************************/

#include <string>

#include "D3DTextInfo.h"

namespace GameUtilities
{

	class D3DText
	{
		/************/
		/* Typedefs */
		/************/
	public:
		typedef std::string Name;

		/****************/
		/* Constructors */
		/****************/
	public:
		D3DText( const D3DTextInfo &info );

		/***********/
		/* Methods */
		/***********/
	public:
		void				  Draw() const;
		
		void		          Set( const D3DTextInfo &info );
		const D3DTextInfo&    Get() const;

		/********/
		/* Data */
		/********/
	private:
		D3DTextInfo    m_info;
	};

	/***********/
	/* Inlines */
	/***********/

	/////////
	// Set //
	/////////
	inline void   
	D3DText::Set( const D3DTextInfo &info )
	{
		m_info = info;
	}
	
	/////////
	// Get //
	/////////
	inline const D3DTextInfo&    
	D3DText::Get() const
	{
		return m_info;
	}

}