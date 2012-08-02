#pragma once

#include <Windows.h>

#include "UtilityError.h"

namespace GameUtilities
{

	class HighResolutionTimer
	{
		/****************/
		/* Constructors */
		/****************/
	public:
		HighResolutionTimer() : m_resetCalled( false )
		{
			BOOL result = QueryPerformanceFrequency( &m_freq );
			if( !result )
				throw UtilityError( "[HighResolutionTimer::HighResolutionTimer]: Timer frequency not found. " );
		}

		/***********/
		/* Methods */
		/***********/
	public:
		void     Reset();
		float    GetElapsedTimeMilli();
		float    GetElapsedTimeSec();

		/********/
		/* Data */
		/********/
	private:
		LARGE_INTEGER    m_freq;
		LARGE_INTEGER    m_lastCount;
		bool             m_resetCalled;
	};

	/***********/
	/* Inlines */
	/***********/

	///////////
	// Reset //
	///////////
	inline void 
	HighResolutionTimer::Reset()
	{
		m_resetCalled = true;
		BOOL result = QueryPerformanceCounter( &m_lastCount );
		if( !result )
			throw UtilityError( "[HighResolutionTimer::Reset]: Could not retrieve current count. " );
	}

	/////////////////////////
	// GetElapsedTimeMilli //
	/////////////////////////
	inline float    
	HighResolutionTimer::GetElapsedTimeMilli()
	{
		if( !m_resetCalled ) return 0.0f;

		LARGE_INTEGER currCount;
		BOOL result = QueryPerformanceCounter( &currCount );
		if( !result )
			throw UtilityError( "[HighResolutionTimer::GetElapsedTimeMilli]: Could not retrieve current count. " );
		return static_cast< float >( 1000.0 * ( currCount.QuadPart - m_lastCount.QuadPart ) * 1.0 / m_freq.QuadPart );
	}

	inline float    
	HighResolutionTimer::GetElapsedTimeSec()
	{
		if( !m_resetCalled ) return 0.0f;

		LARGE_INTEGER currCount;
		BOOL result = QueryPerformanceCounter( &currCount );
		if( !result )
			throw UtilityError( "[HighResolutionTimer::GetElapsedTimeSec]: Could not retrieve current count. " );
		return static_cast< float >( ( currCount.QuadPart - m_lastCount.QuadPart ) * 1.0 / m_freq.QuadPart );
	}

}