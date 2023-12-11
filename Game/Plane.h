// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UnrealMathUtility.h"
#include "Vector.h"
#include "Vector4.h"

/**
 * Structure for three dimensional planes.
 *
 * Stores the coeffecients as Xx+Yy+Zz=W.
 * Note that this is different from many other Plane classes that use Xx+Yy+Zz+W=0.
 */
struct FPlane : public FVector
{
public:

	/** The w-component. */
	float W;

public:

	/** Default constructor (no initialization). */
	inline FPlane();

	/**
	 * Constructor.
	 *
	 * @param V 4D vector to set up plane.
	 */
	inline FPlane(const FVector4& V);

	/**
	 * Constructor.
	 *
	 * @param InX X-coefficient.
	 * @param InY Y-coefficient.
	 * @param InZ Z-coefficient.
	 * @param InW W-coefficient.
	 */
	inline FPlane(float InX, float InY, float InZ, float InW);

	/**
	 * Constructor.
	 *
	 * @param InNormal Plane Normal Vector.
	 * @param InW Plane W-coefficient.
	 */
	inline FPlane(FVector InNormal, float InW);

	/**
	 * Constructor.
	 *
	 * @param InBase Base point in plane.
	 * @param InNormal Plane Normal Vector.
	 */
	inline FPlane(FVector InBase, const FVector& InNormal);

	/**
	 * Constructor.
	 *
	 * @param A First point in the plane.
	 * @param B Second point in the plane.
	 * @param C Third point in the plane.
	 */
	FPlane(FVector A, FVector B, FVector C);

	// Functions.

	/**
	 * Checks if this plane is valid (ie: if it has a non-zero normal).
	 *
	 * @return true if the plane is well-defined (has a non-zero normal), otherwise false.
	 */
	inline bool IsValid() const;

	/**
	 * Get the origin of this plane.
	 *
	 * @return The origin (base point) of this plane.
	 */
	inline FVector GetOrigin() const;

	/**
	 * Get the normal of this plane.
	 *
	 * @return The normal of this plane.
	 */
	inline const FVector& GetNormal() const;


	/**
	 * Calculates distance between plane and a point.
	 *
	 * @param P The other point.
	 * @return The distance from the plane to the point. 0: Point is on the plane. >0: Point is in front of the plane. <0: Point is behind the plane.
	 */
	inline float PlaneDot(const FVector& P) const;

	/**
	 * Normalize this plane in-place if it is larger than a given tolerance. Leaves it unchanged if not.
	 *
	 * @param Tolerance Minimum squared length of vector for normalization.
	 * @return true if the plane was normalized correctly, false otherwise.
	 */
	bool Normalize(float Tolerance = SMALL_NUMBER);

	/**
	 * Get a flipped version of the plane.
	 *
	 * @return A flipped version of the plane.
	 */
	FPlane Flip() const;

	/**
	 * Get the result of transforming the plane by a Matrix.
	 *
	 * @param M The matrix to transform plane with.
	 * @return The result of transform.
	 */
	FPlane TransformBy(const FMatrix& M) const;

	/**
	 * You can optionally pass in the matrices transpose-adjoint, which save it recalculating it.
	 * MSM: If we are going to save the transpose-adjoint we should also save the more expensive
	 * determinant.
	 *
	 * @param M The Matrix to transform plane with.
	 * @param DetM Determinant of Matrix.
	 * @param TA Transpose-adjoint of Matrix.
	 * @return The result of transform.
	 */
	FPlane TransformByUsingAdjointT(const FMatrix& M, float DetM, const FMatrix& TA) const;

	/**
	 * Check if two planes are identical.
	 *
	 * @param V The other plane.
	 * @return true if planes are identical, otherwise false.
	 */
	bool operator==(const FPlane& V) const;

	/**
	 * Check if two planes are different.
	 *
	 * @param V The other plane.
	 * @return true if planes are different, otherwise false.
	 */
	bool operator!=(const FPlane& V) const;

	/**
	 * Checks whether two planes are equal within specified tolerance.
	 *
	 * @param V The other plane.
	 * @param Tolerance Error Tolerance.
	 * @return true if the two planes are equal within specified tolerance, otherwise false.
	 */
	bool Equals(const FPlane& V, float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	 * Calculates dot product of two planes.
	 *
	 * @param V The other plane.
	 * @return The dot product.
	 */
	inline float operator|(const FPlane& V) const;

	/**
	 * Gets result of adding a plane to this.
	 *
	 * @param V The other plane.
	 * @return The result of adding a plane to this.
	 */
	FPlane operator+(const FPlane& V) const;

	/**
	 * Gets result of subtracting a plane from this.
	 *
	 * @param V The other plane.
	 * @return The result of subtracting a plane from this.
	 */
	FPlane operator-(const FPlane& V) const;

	/**
	 * Gets result of dividing a plane.
	 *
	 * @param Scale What to divide by.
	 * @return The result of division.
	 */
	FPlane operator/(float Scale) const;

	/**
	 * Gets result of scaling a plane.
	 *
	 * @param Scale The scaling factor.
	 * @return The result of scaling.
	 */
	FPlane operator*(float Scale) const;

	/**
	 * Gets result of multiplying a plane with this.
	 *
	 * @param V The other plane.
	 * @return The result of multiplying a plane with this.
	 */
	FPlane operator*(const FPlane& V);

	/**
	 * Add another plane to this.
	 *
	 * @param V The other plane.
	 * @return Copy of plane after addition.
	 */
	FPlane operator+=(const FPlane& V);

	/**
	 * Subtract another plane from this.
	 *
	 * @param V The other plane.
	 * @return Copy of plane after subtraction.
	 */
	FPlane operator-=(const FPlane& V);

	/**
	 * Scale this plane.
	 *
	 * @param Scale The scaling factor.
	 * @return Copy of plane after scaling.
	 */
	FPlane operator*=(float Scale);

	/**
	 * Multiply another plane with this.
	 *
	 * @param V The other plane.
	 * @return Copy of plane after multiplication.
	 */
	FPlane operator*=(const FPlane& V);

	/**
	 * Divide this plane.
	 *
	 * @param V What to divide by.
	 * @return Copy of plane after division.
	 */
	FPlane operator/=(float V);

};

/* FVector inline functions
 *****************************************************************************/

inline FVector FVector::MirrorByPlane(const FPlane& Plane) const
{
	return *this - Plane * (2.f * Plane.PlaneDot(*this));
}

inline FVector FVector::PointPlaneProject(const FVector& Point, const FPlane& Plane)
{
	//Find the distance of X from the plane
	//Add the distance back along the normal from the point
	return Point - Plane.PlaneDot(Point) * Plane;
}

inline FVector FVector::PointPlaneProject(const FVector& Point, const FVector& A, const FVector& B, const FVector& C)
{
	//Compute the plane normal from ABC
	FPlane Plane(A, B, C);

	//Find the distance of X from the plane
	//Add the distance back along the normal from the point
	return Point - Plane.PlaneDot(Point) * Plane;
}

/* FPlane inline functions
 *****************************************************************************/

inline FPlane::FPlane() : FVector(0.0f, 0.0f, 0.0f), W(0.0f)
{
}


inline FPlane::FPlane(const FVector4& V)
	: FVector(V.X, V.Y, V.Z)
	, W(V.W)
{
}


inline FPlane::FPlane(float InX, float InY, float InZ, float InW)
	: FVector(InX, InY, InZ)
	, W(InW)
{
}


inline FPlane::FPlane(FVector InNormal, float InW)
	: FVector(InNormal), W(InW)
{
}


inline FPlane::FPlane(FVector InBase, const FVector& InNormal)
	: FVector(InNormal)
	, W(InBase | InNormal)
{
}


inline FPlane::FPlane(FVector A, FVector B, FVector C)
	: FVector(((B - A) ^ (C - A)).GetSafeNormal())
{
	W = A | (FVector)(*this);
}


inline bool FPlane::IsValid() const
{
	return !IsNearlyZero();
}

inline const FVector& FPlane::GetNormal() const
{
	return *this;
}

inline FVector FPlane::GetOrigin() const
{
	return GetNormal() * W;
}


inline float FPlane::PlaneDot(const FVector& P) const
{
	return X * P.X + Y * P.Y + Z * P.Z - W;
}

inline bool FPlane::Normalize(float Tolerance)
{
	const float SquareSum = X * X + Y * Y + Z * Z;
	if (SquareSum > Tolerance)
	{
		const float Scale = FMath::InvSqrt(SquareSum);
		X *= Scale; Y *= Scale; Z *= Scale; W *= Scale;
		return true;
	}
	return false;
}

inline FPlane FPlane::Flip() const
{
	return FPlane(-X, -Y, -Z, -W);
}

inline bool FPlane::operator==(const FPlane& V) const
{
	return (X == V.X) && (Y == V.Y) && (Z == V.Z) && (W == V.W);
}


inline bool FPlane::operator!=(const FPlane& V) const
{
	return (X != V.X) || (Y != V.Y) || (Z != V.Z) || (W != V.W);
}


inline bool FPlane::Equals(const FPlane& V, float Tolerance) const
{
	return (std::abs(X - V.X) < Tolerance) && (std::abs(Y - V.Y) < Tolerance) && (std::abs(Z - V.Z) < Tolerance) && (std::abs(W - V.W) < Tolerance);
}


inline float FPlane::operator|(const FPlane& V) const
{
	return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
}


inline FPlane FPlane::operator+(const FPlane& V) const
{
	return FPlane(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
}


inline FPlane FPlane::operator-(const FPlane& V) const
{
	return FPlane(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
}


inline FPlane FPlane::operator/(float Scale) const
{
	const float RScale = 1.f / Scale;
	return FPlane(X * RScale, Y * RScale, Z * RScale, W * RScale);
}


inline FPlane FPlane::operator*(float Scale) const
{
	return FPlane(X * Scale, Y * Scale, Z * Scale, W * Scale);
}


inline FPlane FPlane::operator*(const FPlane& V)
{
	return FPlane(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
}


inline FPlane FPlane::operator+=(const FPlane& V)
{
	X += V.X; Y += V.Y; Z += V.Z; W += V.W;
	return *this;
}


inline FPlane FPlane::operator-=(const FPlane& V)
{
	X -= V.X; Y -= V.Y; Z -= V.Z; W -= V.W;
	return *this;
}


inline FPlane FPlane::operator*=(float Scale)
{
	X *= Scale; Y *= Scale; Z *= Scale; W *= Scale;
	return *this;
}


inline FPlane FPlane::operator*=(const FPlane& V)
{
	X *= V.X; Y *= V.Y; Z *= V.Z; W *= V.W;
	return *this;
}


inline FPlane FPlane::operator/=(float V)
{
	const float RV = 1.f / V;
	X *= RV; Y *= RV; Z *= RV; W *= RV;
	return *this;
}
