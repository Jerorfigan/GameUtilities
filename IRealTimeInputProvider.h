#pragma once

/****************************************/
/****************************************/
/* Interface to real-time input system. */
/****************************************/
/****************************************/

namespace GameUtilities
{

	class IRealTimeInputProvider
	{
		/************************/
		/* Pure virtual methods */
		/************************/
	public:
		virtual bool IsKeyDown( char asciiChar ) = 0;
		virtual bool IsKeyDown( UINT winVirtualKey ) = 0;

		/**************/
		/* Destructor */
		/**************/
	public:
		~IRealTimeInputProvider() {};
	};

}