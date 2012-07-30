#pragma once

/****************************************/
/****************************************/
/* Interface to real-time input system. */
/****************************************/
/****************************************/

#define KEY( x ) GameUtilities::IRealTimeInputProvider::##x

namespace GameUtilities
{

	class IRealTimeInputProvider
	{
		/*********/
		/* Enums */
		/*********/
	public:
		enum NonCharKey { RightArrow, LeftArrow, UpArrow, DownArrow };

		/************************/
		/* Pure virtual methods */
		/************************/
	public:
		virtual bool IsKeyDown( char asciiChar ) = 0;
		virtual bool IsKeyDown( NonCharKey key ) = 0;

		/**************/
		/* Destructor */
		/**************/
	public:
		~IRealTimeInputProvider() {};
	};

}