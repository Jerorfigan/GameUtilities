#pragma once

/****************************************/
/****************************************/
/* Dual-function 2D point/vector class. */
/****************************************/
/****************************************/

/************************/
/* C++ library includes */
/************************/
#include <cmath>

namespace GameUtilities
{

	struct Point2D
	{
		/****************/
		/* Constructors */
		/****************/
		Point2D() : x(0), y(0) {};
		Point2D( float x, float y ) : x( x ), y( y ) {};

		/***********/
		/* Methods */
		/***********/
		float    Mag();
		float    MagSqr();

		/*************/
		/* Operators */
		/*************/
		Point2D    operator+( const Point2D &rhs ) const;
		Point2D    operator-( const Point2D &rhs ) const;
		Point2D    operator*( const float &rhs ) const;

		/********/
		/* Data */
		/********/
		float x;
		float y;
	};

	/***********/
	/* Inlines */
	/***********/
	inline float    Point2D::Mag()
	{
		return std::sqrt( x * x + y * y );
	}

	inline float    Point2D::MagSqr()
	{
		return x * x + y * y;
	}

	/********************/
	/* Operator Inlines */
	/********************/
	inline Point2D    Point2D::operator+( const Point2D &rhs ) const
	{
		return Point2D( x + rhs.x, y + rhs.y );
	}

	inline Point2D    Point2D::operator-( const Point2D &rhs ) const
	{
		return Point2D( x - rhs.x, y - rhs.y );
	}

	inline Point2D    Point2D::operator*( const float &rhs ) const
	{
		return Point2D( x * rhs, y * rhs );
	}

	/************************/
	/* Non-member operators */
	/************************/
	inline Point2D    operator*( const float &lhs, const Point2D &rhs )
	{
		return Point2D( rhs.x * lhs, rhs.y * lhs );
	}
}