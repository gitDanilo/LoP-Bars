// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UnrealMathUtility.h"

/**
 * Structure for integer points in 2-d space.
 *
 * @todo Docs: The operators need better documentation, i.e. what does it mean to divide a point?
 */
struct FIntPoint
{
	/** Holds the point's x-coordinate. */
	int X;

	/** Holds the point's y-coordinate. */
	int Y;

public:

	/** Default constructor (no initialization). */
	FIntPoint();

	/**
	 * Create and initialize a new instance with the specified coordinates.
	 *
	 * @param InX The x-coordinate.
	 * @param InY The y-coordinate.
	 */
	FIntPoint(int InX, int InY);

	/**
	 * Create and initialize a new instance with a single int.
	 * Both X and Y will be initialized to this value
	 *
	 * @param InXY The x and y-coordinate.
	 */
	FIntPoint(int InXY);

public:

	/**
	 * Get specific component of a point.
	 *
	 * @param PointIndex Index of point component.
	 * @return const reference to component.
	 */
	const int& operator()(int PointIndex) const;

	/**
	 * Get specific component of a point.
	 *
	 * @param PointIndex Index of point component
	 * @return reference to component.
	 */
	int& operator()(int PointIndex);

	/**
	 * Compare two points for equality.
	 *
	 * @param Other The other int point being compared.
	 * @return true if the points are equal, false otherwise.
	 */
	bool operator==(const FIntPoint& Other) const;

	/**
	 * Compare two points for inequality.
	 *
	 * @param Other The other int point being compared.
	 * @return true if the points are not equal, false otherwise.
	 */
	bool operator!=(const FIntPoint& Other) const;

	/**
	 * Scale this point.
	 *
	 * @param Scale What to multiply the point by.
	 * @return Reference to this point after multiplication.
	 */
	FIntPoint& operator*=(int Scale);

	/**
	 * Divide this point by a scalar.
	 *
	 * @param Divisor What to divide the point by.
	 * @return Reference to this point after division.
	 */
	FIntPoint& operator/=(int Divisor);

	/**
	 * Add another point component-wise to this point.
	 *
	 * @param Other The point to add to this point.
	 * @return Reference to this point after addition.
	 */
	FIntPoint& operator+=(const FIntPoint& Other);

	/**
	 * Multiply another point component-wise from this point.
	 *
	 * @param Other The point to multiply with this point.
	 * @return Reference to this point after multiplication.
	 */
	FIntPoint& operator*=(const FIntPoint& Other);

	/**
	 * Subtract another point component-wise from this point.
	 *
	 * @param Other The point to subtract from this point.
	 * @return Reference to this point after subtraction.
	 */
	FIntPoint& operator-=(const FIntPoint& Other);

	/**
	 * Divide this point component-wise by another point.
	 *
	 * @param Other The point to divide with.
	 * @return Reference to this point after division.
	 */
	FIntPoint& operator/=(const FIntPoint& Other);

	/**
	 * Assign another point to this one.
	 *
	 * @param Other The point to assign this point from.
	 * @return Reference to this point after assignment.
	 */
	FIntPoint& operator=(const FIntPoint& Other);

	/**
	 * Get the result of scaling on this point.
	 *
	 * @param Scale What to multiply the point by.
	 * @return A new scaled int point.
	 */
	FIntPoint operator*(int Scale) const;

	/**
	 * Get the result of division on this point.
	 *
	 * @param Divisor What to divide the point by.
	 * @return A new divided int point.
	 */
	FIntPoint operator/(int Divisor) const;

	/**
	 * Get the result of addition on this point.
	 *
	 * @param Other The other point to add to this.
	 * @return A new combined int point.
	 */
	FIntPoint operator+(const FIntPoint& Other) const;

	/**
	 * Get the result of subtraction from this point.
	 *
	 * @param Other The other point to subtract from this.
	 * @return A new subtracted int point.
	 */
	FIntPoint operator-(const FIntPoint& Other) const;

	/**
	 * Get the result of multiplication on this point.
	 *
	 * @param Other The point to multiply with this point.
	 * @return A new multiplied int point
	 */
	FIntPoint operator*(const FIntPoint& Other) const;

	/**
	 * Get the result of division on this point.
	 *
	 * @param Other The other point to subtract from this.
	 * @return A new subtracted int point.
	 */
	FIntPoint operator/(const FIntPoint& Other) const;

	/**
	* Get specific component of the point.
	*
	* @param Index the index of point component
	* @return reference to component.
	*/
	int& operator[](int Index);

	/**
	* Get specific component of the point.
	*
	* @param Index the index of point component
	* @return copy of component value.
	*/
	int operator[](int Index) const;

public:

	/**
	 * Get the component-wise min of two points.
	 *
	 * @see ComponentMax, GetMax
	 */
	inline FIntPoint ComponentMin(const FIntPoint& Other) const;

	/**
	 * Get the component-wise max of two points.
	 *
	 * @see ComponentMin, GetMin
	 */
	inline FIntPoint ComponentMax(const FIntPoint& Other) const;

	/**
	 * Get the larger of the point's two components.
	 *
	 * @return The maximum component of the point.
	 * @see GetMin, Size, SizeSquared
	 */
	int GetMax() const;

	/**
	 * Get the smaller of the point's two components.
	 *
	 * @return The minimum component of the point.
	 * @see GetMax, Size, SizeSquared
	 */
	int GetMin() const;

	/**
	 * Get the distance of this point from (0,0).
	 *
	 * @return The distance of this point from (0,0).
	 * @see GetMax, GetMin, SizeSquared
	 */
	int Size() const;

	/**
	 * Get the squared distance of this point from (0,0).
	 *
	 * @return The squared distance of this point from (0,0).
	 * @see GetMax, GetMin, Size
	 */
	int SizeSquared() const;

public:

	/**
	 * Divide an int point and round up the result.
	 *
	 * @param lhs The int point being divided.
	 * @param Divisor What to divide the int point by.
	 * @return A new divided int point.
	 * @see DivideAndRoundDown
	 */
	static FIntPoint DivideAndRoundUp(FIntPoint lhs, int Divisor);
	static FIntPoint DivideAndRoundUp(FIntPoint lhs, FIntPoint Divisor);

	/**
	 * Divide an int point and round down the result.
	 *
	 * @param lhs The int point being divided.
	 * @param Divisor What to divide the int point by.
	 * @return A new divided int point.
	 * @see DivideAndRoundUp
	 */
	static FIntPoint DivideAndRoundDown(FIntPoint lhs, int Divisor);

	/**
	 * Get number of components point has.
	 *
	 * @return number of components point has.
	 */
	static int Num();
};


/* FIntPoint inline functions
 *****************************************************************************/

inline FIntPoint::FIntPoint() : X(0), Y(0)
{

}

inline FIntPoint::FIntPoint(int InX, int InY)
	: X(InX)
	, Y(InY)
{

}

inline FIntPoint::FIntPoint(int InXY)
	: X(InXY)
	, Y(InXY)
{

}

inline const int& FIntPoint::operator()(int PointIndex) const
{
	return (&X)[PointIndex];
}


inline int& FIntPoint::operator()(int PointIndex)
{
	return (&X)[PointIndex];
}


inline int FIntPoint::Num()
{
	return 2;
}


inline bool FIntPoint::operator==(const FIntPoint& Other) const
{
	return X == Other.X && Y == Other.Y;
}


inline bool FIntPoint::operator!=(const FIntPoint& Other) const
{
	return (X != Other.X) || (Y != Other.Y);
}

inline FIntPoint& FIntPoint::operator*=(int Scale)
{
	X *= Scale;
	Y *= Scale;

	return *this;
}

inline FIntPoint& FIntPoint::operator/=(int Divisor)
{
	X /= Divisor;
	Y /= Divisor;

	return *this;
}


inline FIntPoint& FIntPoint::operator+=(const FIntPoint& Other)
{
	X += Other.X;
	Y += Other.Y;

	return *this;
}


inline FIntPoint& FIntPoint::operator-=(const FIntPoint& Other)
{
	X -= Other.X;
	Y -= Other.Y;

	return *this;
}


inline FIntPoint& FIntPoint::operator*=(const FIntPoint& Other)
{
	X *= Other.X;
	Y *= Other.Y;

	return *this;
}


inline FIntPoint& FIntPoint::operator/=(const FIntPoint& Other)
{
	X /= Other.X;
	Y /= Other.Y;

	return *this;
}


inline FIntPoint& FIntPoint::operator=(const FIntPoint& Other)
{
	X = Other.X;
	Y = Other.Y;

	return *this;
}


inline FIntPoint FIntPoint::operator*(int Scale) const
{
	return FIntPoint(*this) *= Scale;
}


inline FIntPoint FIntPoint::operator/(int Divisor) const
{
	return FIntPoint(*this) /= Divisor;
}


inline int& FIntPoint::operator[](int Index)
{
	return ((Index == 0) ? X : Y);
}


inline int FIntPoint::operator[](int Index) const
{
	return ((Index == 0) ? X : Y);
}


inline FIntPoint FIntPoint::ComponentMin(const FIntPoint& Other) const
{
	return FIntPoint(MIN(X, Other.X), MIN(Y, Other.Y));
}


inline FIntPoint FIntPoint::ComponentMax(const FIntPoint& Other) const
{
	return FIntPoint(MAX(X, Other.X), MAX(Y, Other.Y));
}

inline FIntPoint FIntPoint::DivideAndRoundUp(FIntPoint lhs, int Divisor)
{
	return FIntPoint(FMath::DivideAndRoundUp(lhs.X, Divisor), FMath::DivideAndRoundUp(lhs.Y, Divisor));
}

inline FIntPoint FIntPoint::DivideAndRoundUp(FIntPoint lhs, FIntPoint Divisor)
{
	return FIntPoint(FMath::DivideAndRoundUp(lhs.X, Divisor.X), FMath::DivideAndRoundUp(lhs.Y, Divisor.Y));
}

inline FIntPoint FIntPoint::DivideAndRoundDown(FIntPoint lhs, int Divisor)
{
	return FIntPoint(FMath::DivideAndRoundDown(lhs.X, Divisor), FMath::DivideAndRoundDown(lhs.Y, Divisor));
}


inline FIntPoint FIntPoint::operator+(const FIntPoint& Other) const
{
	return FIntPoint(*this) += Other;
}


inline FIntPoint FIntPoint::operator-(const FIntPoint& Other) const
{
	return FIntPoint(*this) -= Other;
}


inline FIntPoint FIntPoint::operator*(const FIntPoint& Other) const
{
	return FIntPoint(*this) *= Other;
}


inline FIntPoint FIntPoint::operator/(const FIntPoint& Other) const
{
	return FIntPoint(*this) /= Other;
}


inline int FIntPoint::GetMax() const
{
	return MAX(X, Y);
}


inline int FIntPoint::GetMin() const
{
	return MIN(X, Y);
}


inline int FIntPoint::Size() const
{
	long long X64 = (long long)X;
	long long Y64 = (long long)Y;
	return int(std::sqrt(float(X64 * X64 + Y64 * Y64)));
}

inline int FIntPoint::SizeSquared() const
{
	return X * X + Y * Y;
}
