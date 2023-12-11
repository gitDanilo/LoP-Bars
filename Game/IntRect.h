// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UnrealMathUtility.h"
#include "IntPoint.h"
#include "Vector2D.h"


/**
 * Structure for integer rectangles in 2-d space.
 *
 * @todo Docs: The operators need better documentation, i.e. what does it mean to divide a rectangle?
 */
struct FIntRect
{
	/** Holds the first pixel line/row (like in Win32 RECT). */
	FIntPoint Min;

	/** Holds the last pixel line/row (like in Win32 RECT). */
	FIntPoint Max;

public:

	/** Constructor */
	FIntRect();

	/**
	 * Constructor
	 *
	 * @param X0 Minimum X coordinate.
	 * @param Y0 Minimum Y coordinate.
	 * @param X1 Maximum X coordinate.
	 * @param Y1 Maximum Y coordinate.
	 */
	FIntRect(int X0, int Y0, int X1, int Y1);

	/**
	 * Constructor
	 *
	 * @param InMin Minimum Point
	 * @param InMax Maximum Point
	 */
	FIntRect(FIntPoint InMin, FIntPoint InMax);

public:

	/**
	 * Gets a specific point in this rectangle.
	 *
	 * @param PointIndex Index of Point in rectangle.
	 * @return Const reference to point in rectangle.
	 */
	const FIntPoint& operator()(int PointIndex) const;

	/**
	 * Gets a specific point in this rectangle.
	 *
	 * @param PointIndex Index of Point in rectangle.
	 * @return Reference to point in rectangle.
	 */
	FIntPoint& operator()(int PointIndex);

	/**
	 * Compares Rectangles for equality.
	 *
	 * @param Other The Other Rectangle for comparison.
	 * @return true if the rectangles are equal, false otherwise..
	 */
	bool operator==(const FIntRect& Other) const;

	/**
	 * Compares Rectangles for inequality.
	 *
	 * @param Other The Other Rectangle for comparison.
	 * @return true if the rectangles are not equal, false otherwise..
	 */
	bool operator!=(const FIntRect& Other) const;

	/**
	 * Applies scaling to this rectangle.
	 *
	 * @param Scale What to multiply the rectangle by.
	 * @return Reference to this rectangle after scaling.
	 */
	FIntRect& operator*=(int Scale);

	/**
	 * Adds a point to this rectangle.
	 *
	 * @param Point The point to add onto both points in the rectangle.
	 * @return Reference to this rectangle after addition.
	 */
	FIntRect& operator+=(const FIntPoint& Point);

	/**
	 * Subtracts a point from this rectangle.
	 *
	 * @param Point The point to subtract from both points in the rectangle.
	 * @return Reference to this rectangle after subtraction.
	 */
	FIntRect& operator-=(const FIntPoint& Point);

	/**
	 * Gets the result of scaling on this rectangle.
	 *
	 * @param Scale What to multiply this rectangle by.
	 * @return New scaled rectangle.
	 */
	FIntRect operator*(int Scale) const;

	/**
	 * Gets the result of division on this rectangle.
	 *
	 * @param Div What to divide this rectangle by.
	 * @return New divided rectangle.
	 */
	FIntRect operator/(int Div) const;

	/**
	 * Gets the result of adding a point to this rectangle.
	 *
	 * @param Point The point to add to both points in the rectangle.
	 * @return New rectangle with point added to it.
	 */
	FIntRect operator+(const FIntPoint& Point) const;

	/**
	 * Gets the result of dividing a point with this rectangle.
	 *
	 * @param Point The point to divide with.
	 * @return New rectangle with point divided.
	 */
	FIntRect operator/(const FIntPoint& Point) const;

	/**
	 * Gets the result of subtracting a point from this rectangle.
	 *
	 * @param Point The point to subtract from both points in the rectangle.
	 * @return New rectangle with point subtracted from it.
	 */
	FIntRect operator-(const FIntPoint& Point) const;

	/**
	 * Gets the result of adding two rectangles together.
	 *
	 * @param Other The other rectangle to add to this.
	 * @return New rectangle after both are added together.
	 */
	FIntRect operator+(const FIntRect& Other) const;

	/**
	 * Gets the result of subtracting a rectangle from this one.
	 *
	 * @param Other The other rectangle to subtract from this.
	 * @return New rectangle after one is subtracted from this.
	 */
	FIntRect operator-(const FIntRect& Other) const;

public:

	/**
	 * Calculates the area of this rectangle.
	 *
	 * @return The area of this rectangle.
	 */
	int Area() const;

	/**
	 * Creates a rectangle from the bottom part of this rectangle.
	 *
	 * @param InHeight Height of the new rectangle (<= rectangles original height).
	 * @return The new rectangle.
	 */
	FIntRect Bottom(int InHeight) const;

	/**
	 * Clip a rectangle using the bounds of another rectangle.
	 *
	 * @param Other The other rectangle to clip against.
	 */
	void Clip(const FIntRect& Other);

	/** Combines the two rectanges. */
	void Union(const FIntRect& Other);

	/**
	 * Test whether this rectangle contains a point.
	 *
	 * @param Point The point to test against.
	 * @return true if the rectangle contains the specified point,, false otherwise..
	 */
	bool Contains(FIntPoint Point) const;

	/**
	 * Gets the Center and Extents of this rectangle.
	 *
	 * @param OutCenter Will contain the center point.
	 * @param OutExtent Will contain the extent.
	 */
	void GetCenterAndExtents(FIntPoint& OutCenter, FIntPoint& OutExtent) const;

	/**
	 * Gets the Height of the rectangle.
	 *
	 * @return The Height of the rectangle.
	 */
	int Height() const;

	/**
	 * Inflates or deflates the rectangle.
	 *
	 * @param Amount The amount to inflate or deflate the rectangle on each side.
	 */
	void InflateRect(int Amount);

	/**
	 * Adds to this rectangle to include a given point.
	 *
	 * @param Point The point to increase the rectangle to.
	 */
	void Include(FIntPoint Point);

	/**
	 * Gets a new rectangle from the inner of this one.
	 *
	 * @param Shrink How much to remove from each point of this rectangle.
	 * @return New inner Rectangle.
	 */
	FIntRect Inner(FIntPoint Shrink) const;

	/**
	 * Creates a rectangle from the right hand side of this rectangle.
	 *
	 * @param InWidth Width of the new rectangle (<= rectangles original width).
	 * @return The new rectangle.
	 */
	FIntRect Right(int InWidth) const;

	/**
	 * Scales a rectangle using a floating point number.
	 *
	 * @param Fraction What to scale the rectangle by
	 * @return New scaled rectangle.
	 */
	FIntRect Scale(float Fraction) const;

	/**
	 * Gets the distance from one corner of the rectangle to the other.
	 *
	 * @return The distance from one corner of the rectangle to the other.
	 */
	FIntPoint Size() const;

	/**
	 * Gets the width of the rectangle.
	 *
	 * @return The width of the rectangle.
	 */
	int Width() const;

	/**
	 * Returns true if the rectangle is 0 x 0.
	 *
	 * @return true if the rectangle is 0 x 0.
	 */
	bool IsEmpty() const;

public:

	/**
	 * Divides a rectangle and rounds up to the nearest integer.
	 *
	 * @param lhs The Rectangle to divide.
	 * @param Div What to divide by.
	 * @return New divided rectangle.
	 */
	static FIntRect DivideAndRoundUp(FIntRect lhs, int Div);
	static FIntRect DivideAndRoundUp(FIntRect lhs, FIntPoint Div);

	/**
	 * Gets number of points in the Rectangle.
	 *
	 * @return Number of points in the Rectangle.
	 */
	static int Num();
};


inline FIntRect FIntRect::Scale(float Fraction) const
{
	FVector2D Min2D = FVector2D((float)Min.X, (float)Min.Y) * Fraction;
	FVector2D Max2D = FVector2D((float)Max.X, (float)Max.Y) * Fraction;

	return FIntRect((int)std::floor(Min2D.X), (int)std::floor(Min2D.Y), (int)std::ceil(Max2D.X), (int)std::ceil(Max2D.Y));
}


/* FIntRect inline functions
 *****************************************************************************/

inline FIntRect::FIntRect()
	: Min(0, 0)
	, Max(0, 0)
{
}


inline FIntRect::FIntRect(int X0, int Y0, int X1, int Y1)
	: Min(X0, Y0)
	, Max(X1, Y1)
{
}


inline FIntRect::FIntRect(FIntPoint InMin, FIntPoint InMax)
	: Min(InMin)
	, Max(InMax)
{
}


inline const FIntPoint& FIntRect::operator()(int PointIndex) const
{
	return (&Min)[PointIndex];
}


inline FIntPoint& FIntRect::operator()(int PointIndex)
{
	return (&Min)[PointIndex];
}


inline bool FIntRect::operator==(const FIntRect& Other) const
{
	return Min == Other.Min && Max == Other.Max;
}


inline bool FIntRect::operator!=(const FIntRect& Other) const
{
	return Min != Other.Min || Max != Other.Max;
}


inline FIntRect& FIntRect::operator*=(int Scale)
{
	Min *= Scale;
	Max *= Scale;

	return *this;
}


inline FIntRect& FIntRect::operator+=(const FIntPoint& Point)
{
	Min += Point;
	Max += Point;

	return *this;
}


inline FIntRect& FIntRect::operator-=(const FIntPoint& Point)
{
	Min -= Point;
	Max -= Point;

	return *this;
}


inline FIntRect FIntRect::operator*(int Scale) const
{
	return FIntRect(Min * Scale, Max * Scale);
}


inline FIntRect FIntRect::operator/(int Div) const
{
	return FIntRect(Min / Div, Max / Div);
}


inline FIntRect FIntRect::operator+(const FIntPoint& Point) const
{
	return FIntRect(Min + Point, Max + Point);
}


inline FIntRect FIntRect::operator/(const FIntPoint& Point) const
{
	return FIntRect(Min / Point, Max / Point);
}


inline FIntRect FIntRect::operator-(const FIntPoint& Point) const
{
	return FIntRect(Min - Point, Max - Point);
}


inline FIntRect FIntRect::operator+(const FIntRect& Other) const
{
	return FIntRect(Min + Other.Min, Max + Other.Max);
}


inline FIntRect FIntRect::operator-(const FIntRect& Other) const
{
	return FIntRect(Min - Other.Min, Max - Other.Max);
}


inline int FIntRect::Area() const
{
	return (Max.X - Min.X) * (Max.Y - Min.Y);
}


inline FIntRect FIntRect::Bottom(int InHeight) const
{
	return FIntRect(Min.X, MAX(Min.Y, Max.Y - InHeight), Max.X, Max.Y);
}


inline void FIntRect::Clip(const FIntRect& R)
{
	Min.X = MAX(Min.X, R.Min.X);
	Min.Y = MAX(Min.Y, R.Min.Y);
	Max.X = MIN(Max.X, R.Max.X);
	Max.Y = MIN(Max.Y, R.Max.Y);

	// return zero area if not overlapping
	Max.X = MAX(Min.X, Max.X);
	Max.Y = MAX(Min.Y, Max.Y);
}

inline void FIntRect::Union(const FIntRect& R)
{
	Min.X = MIN(Min.X, R.Min.X);
	Min.Y = MIN(Min.Y, R.Min.Y);
	Max.X = MAX(Max.X, R.Max.X);
	Max.Y = MAX(Max.Y, R.Max.Y);
}

inline bool FIntRect::Contains(FIntPoint P) const
{
	return P.X >= Min.X && P.X < Max.X && P.Y >= Min.Y && P.Y < Max.Y;
}


inline FIntRect FIntRect::DivideAndRoundUp(FIntRect lhs, int Div)
{
	return DivideAndRoundUp(lhs, FIntPoint(Div, Div));
}

inline FIntRect FIntRect::DivideAndRoundUp(FIntRect lhs, FIntPoint Div)
{
	return FIntRect(lhs.Min / Div, FIntPoint::DivideAndRoundUp(lhs.Max, Div));
}

inline void FIntRect::GetCenterAndExtents(FIntPoint& OutCenter, FIntPoint& OutExtent) const
{
	OutExtent.X = (Max.X - Min.X) / 2;
	OutExtent.Y = (Max.Y - Min.Y) / 2;

	OutCenter.X = Min.X + OutExtent.X;
	OutCenter.Y = Min.Y + OutExtent.Y;
}


inline int FIntRect::Height() const
{
	return (Max.Y - Min.Y);
}


inline void FIntRect::InflateRect(int Amount)
{
	Min.X -= Amount;
	Min.Y -= Amount;
	Max.X += Amount;
	Max.Y += Amount;
}


inline void FIntRect::Include(FIntPoint Point)
{
	Min.X = MIN(Min.X, Point.X);
	Min.Y = MIN(Min.Y, Point.Y);
	Max.X = MAX(Max.X, Point.X);
	Max.Y = MAX(Max.Y, Point.Y);
}

inline FIntRect FIntRect::Inner(FIntPoint Shrink) const
{
	return FIntRect(Min + Shrink, Max - Shrink);
}


inline int FIntRect::Num()
{
	return 2;
}


inline FIntRect FIntRect::Right(int InWidth) const
{
	return FIntRect(MAX(Min.X, Max.X - InWidth), Min.Y, Max.X, Max.Y);
}


inline FIntPoint FIntRect::Size() const
{
	return FIntPoint(Max.X - Min.X, Max.Y - Min.Y);
}

inline int FIntRect::Width() const
{
	return Max.X - Min.X;
}

inline bool FIntRect::IsEmpty() const
{
	return Width() == 0 && Height() == 0;
}
