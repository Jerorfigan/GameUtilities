#include "stdafx.h"

#include "D3DSpriteDrawQueue.h"
#include "UtilityError.h"

namespace GameUtilities
{

	/***************/
	/* Static Data */
	/***************/
	D3DSpriteDrawQueue*    D3DSpriteDrawQueue::m_pSpriteDrawQueue = NULL;

	/******************/
	/* Static Methods */
	/******************/
	
	////////////
	// Create //
	////////////
	void    
	D3DSpriteDrawQueue::Create()
	{
		new D3DSpriteDrawQueue();
	}

	/////////////
	// Destroy //
	/////////////
	void    
	D3DSpriteDrawQueue::Destroy()
	{
		delete m_pSpriteDrawQueue;
		m_pSpriteDrawQueue = NULL;
	}

	/****************/
	/* Constructors */
	/****************/
	D3DSpriteDrawQueue::D3DSpriteDrawQueue()
	{
		if( m_pSpriteDrawQueue )
			throw UtilityError( "[D3DSpriteDrawQueue::D3DSpriteDrawQueue]: Attempt to instantiate multiple instances of singleton D3DSpriteDrawQueue." );

		m_pSpriteDrawQueue = this;
	}

	/***********/
	/* Methods */
	/***********/
	
	////////////////////
	// AddToDrawQueue //
	////////////////////
	void    
	D3DSpriteDrawQueue::AddToDrawQueue( D3DSprite *sprite )
	{
		// Order sprites by z-depth (ascending) as they're added so that sprites further back in the scene are drawn
		// first.
		bool spriteInserted = false;
		for( SpriteQueue::iterator spriteItr = m_drawQueue.begin();
			 spriteItr != m_drawQueue.end(); ++spriteItr )
		{
			if( sprite->m_info.zDepth > (*spriteItr)->m_info.zDepth )
			{
				m_drawQueue.insert( spriteItr, sprite );
				spriteInserted = true;
				break;
			}
		}

		// If sprite wasn't inserted, then either the queue is empty or sprite belongs all the way at the back.
		// Either way, stick at end.
		if( !spriteInserted )
			m_drawQueue.push_back( sprite );
	}

	//////////
	// Draw //
	//////////
	void    
	D3DSpriteDrawQueue::Draw()
	{
		for( SpriteQueue::iterator spriteItr = m_drawQueue.begin();
			 spriteItr != m_drawQueue.end(); ++spriteItr )
		{
			(*spriteItr)->Draw();
		}

		// Clear draw queue
		m_drawQueue.clear();
	}

}