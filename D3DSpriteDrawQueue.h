#pragma once

#include <list>

#include "D3DSprite.h"

namespace GameUtilities
{

	class D3DSpriteDrawQueue
	{
		/************/
		/* Typedefs */
		/************/
	private:
		typedef std::list< D3DSprite* > SpriteQueue;

		/***************/
		/* Static Data */
		/***************/
	private:
		static D3DSpriteDrawQueue*    m_pSpriteDrawQueue;

		/******************/
		/* Static Methods */
		/******************/
	public:
		static void    Create();
		static void    Destroy();
		static		   D3DSpriteDrawQueue* GetSpriteDrawQueue();

		/****************/
		/* Constructors */
		/****************/
	public:
		D3DSpriteDrawQueue();

		/***********/
		/* Methods */
		/***********/
	public:
		void    AddToDrawQueue( D3DSprite *sprite );
		void    Draw();

		/********/
		/* Data */
		/********/
	private:
		SpriteQueue    m_drawQueue;
	};

	/******************/
	/* Static Inlines */
	/******************/		   
	inline D3DSpriteDrawQueue* 
	D3DSpriteDrawQueue::GetSpriteDrawQueue()
	{
		return m_pSpriteDrawQueue;
	}

	/* Global abbreviated wrapper for D3DSpriteDrawQueue::GetSpriteDrawQueue */
	inline D3DSpriteDrawQueue*
	SpriteDrawQueue()
	{
		return D3DSpriteDrawQueue::GetSpriteDrawQueue();
	}

}