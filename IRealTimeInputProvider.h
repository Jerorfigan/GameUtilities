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
		virtual bool IsKeyDown( char key ) = 0;
	};

}