#pragma once

/*********************************/
/*********************************/
/* Interface to graphics system. */
/*********************************/
/*********************************/
#include <Windows.h>
#include <string>

#include "Globals.h"
#include "Point2D.h"

namespace GameUtilities
{

	class IGraphicsProvider
	{
		/************/
		/* Typedefs */
		/************/
	public:
		typedef std::size_t SpriteCollectionID;

		/********************/
		/* Internal classes */
		/********************/
	public: 
		struct SpriteInfo
		{
			std::string    imageFile;
			RECT           subrect;
			Point2D		   center;    // In subrect pixels. Reference point for rotation/scale.
			Point2D		   position;  // In screen pixels
			float		   rotation;  // In degrees. Positive for CW.
			float		   scale;     // 0-1(shrink), >1(grow)
			float		   alpha;     // 0(trans)-1(opaque)
		};

		/************************/
		/* Pure virtual methods */
		/************************/
	public:
		/* Backbuffer management */
		virtual void                  BeginScene() = 0;
		virtual void                  EndScene() = 0;
		virtual void                  ClearBackbuffer() = 0;
		virtual void                  Flip() = 0;

		/* Sprite management. */
		virtual	SpriteCollectionID    CreateSpriteCollection() = 0;
		virtual void				  AddSprite( SpriteCollectionID id, std::string name, const SpriteInfo &info ) = 0;
		virtual void                  RemoveSprite( SpriteCollectionID id, std::string name ) = 0;
		virtual void			      SetSprite( SpriteCollectionID id, std::string name, const SpriteInfo &info ) = 0;
		virtual SpriteInfo		      GetSprite( SpriteCollectionID id, std::string name ) = 0;
		virtual void				  DrawSpriteCollection( SpriteCollectionID id ) = 0;
		virtual void				  StartSpriteBatch() = 0;
		virtual void				  EndSpriteBatch() = 0;

		/**************/
		/* Destructor */
		/**************/
	public:
		~IGraphicsProvider() {};
	};

}