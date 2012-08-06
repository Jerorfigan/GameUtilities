#pragma once

/***************************************************************/
/***************************************************************/
/* Holds a collection of text objects tied to a collection ID. */
/***************************************************************/
/***************************************************************/

#include <map>

#include "D3DText.h"
#include "UtilityError.h"

namespace GameUtilities
{

	class D3DTextCollection
	{
		/************/
		/* Typedefs */
		/************/
	public:
		typedef std::size_t ID;
		typedef std::map< D3DText::Name, D3DText* > TextName2Text;

		/****************/
		/* Constructors */
		/****************/
	public:
		D3DTextCollection() : m_ID( m_IDSequence++ ) {}

		/***********/
		/* Methods */
		/***********/
	public:
		void		DrawCollection();
		void		AddText( D3DText::Name name, D3DText *pText );
		void		RemoveText( D3DText::Name name );
		D3DText*    GetText( D3DText::Name name );
		ID			GetID();

		~D3DTextCollection();

	private:
		void		VerifyTextName( D3DText::Name name, bool isPresent = true ); 

		/********/
		/* Data */
		/********/
	private:
		TextName2Text    m_textName2Text;
		ID				 m_ID;

		/***************/
		/* Static Data */
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
	D3DTextCollection::DrawCollection()
	{
		for( TextName2Text::iterator textItr = m_textName2Text.begin();
			 textItr != m_textName2Text.end(); ++textItr )
		{
			textItr->second->Draw();
		}
	}

	/////////////
	// AddText //
	/////////////
	inline void		
	D3DTextCollection::AddText( D3DText::Name name, D3DText *pText )
	{
		VerifyTextName( name, false );
		m_textName2Text[ name ] = pText;
	}

	////////////////
	// RemoveText //
	////////////////
	inline void		
	D3DTextCollection::RemoveText( D3DText::Name name )
	{
		VerifyTextName( name );
		m_textName2Text.erase( name );
	}

	/////////////
	// GetText //
	/////////////
	inline D3DText*    
	D3DTextCollection::GetText( D3DText::Name name )
	{
		VerifyTextName( name );
		return m_textName2Text[ name ];
	}

	///////////
	// GetID //
	///////////
	inline D3DTextCollection::ID			
	D3DTextCollection::GetID()
	{
		return m_ID;
	}

	//////////////////////
	// VerifyTextName //
	//////////////////////
	inline void		  
	D3DTextCollection::VerifyTextName( D3DText::Name name, bool isPresent )
	{
		TextName2Text::iterator findResult = m_textName2Text.find( name );
		if( findResult == m_textName2Text.end() && isPresent )
			throw UtilityError( "[D3DTextCollection::VerifyTextName]: Invalid text name passed to D3DGraphicsProvider." );
		else if( findResult != m_textName2Text.end() && !isPresent )
			throw UtilityError( "[D3DTextCollection::VerifyTextName]: Text name passed to D3DGraphicsProvider already in use." );
	}

	////////////////
	// Destructor //
	////////////////
	inline D3DTextCollection::~D3DTextCollection()
	{
		// Free D3DText objects
		for( TextName2Text::iterator textItr = m_textName2Text.begin();
			 textItr != m_textName2Text.end(); ++textItr )
		{
			delete textItr->second;
		}
	}
}