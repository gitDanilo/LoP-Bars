// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UnrealMathUtility.h"
#include "IntPoint.h"
#include "Vector2D.h"

/**
 * A vector in 3-D space composed of components (X, Y, Z) with floating point precision.
 */
struct FVector
{
public:

	/** Vector's X component. */
	float X;

	/** Vector's Y component. */
	float Y;

	/** Vector's Z component. */
	float Z;

public:
	static const FVector ZeroVector;

	/** Default constructor (no initialization). */
	inline FVector();

	/**
	 * Constructor initializing all components to a single float value.
	 *
	 * @param InF Value to set all components to.
	 */
	explicit inline FVector(float InF);

	/**
	 * Constructor using the XYZ components from a 4D vector.
	 *
	 * @param V 4D Vector to copy from.
	 */
	inline FVector(const FVector4& V);

	/**
	 * Constructor using initial values for each component.
	 *
	 * @param InX X Coordinate.
	 * @param InY Y Coordinate.
	 * @param InZ Z Coordinate.
	 */
	inline FVector(float InX, float InY, float InZ);

	/**
	 * Constructs a vector from an FVector2D and Z value.
	 *
	 * @param V Vector to copy from.
	 * @param InZ Z Coordinate.
	 */
	explicit inline FVector(const FVector2D V, float InZ);

	/**
	 * Constructs a vector from an FIntPoint.
	 *
	 * @param A Int Point used to set X and Y coordinates, Z is set to zero.
	 */
	explicit FVector(FIntPoint A);

	inline FVector& operator=(const FVector& Other);

	/**
	 * Calculate cross product between this and another vector.
	 *
	 * @param V The other vector.
	 * @return The cross product.
	 */
	inline FVector operator^(const FVector& V) const;

	/**
	 * Calculate the cross product of two vectors.
	 *
	 * @param A The first vector.
	 * @param B The second vector.
	 * @return The cross product.
	 */
	inline static FVector CrossProduct(const FVector& A, const FVector& B);

	/**
	 * Calculate the dot product between this and another vector.
	 *
	 * @param V The other vector.
	 * @return The dot product.
	 */
	inline float operator|(const FVector& V) const;

	/**
	 * Calculate the dot product of two vectors.
	 *
	 * @param A The first vector.
	 * @param B The second vector.
	 * @return The dot product.
	 */
	inline static float DotProduct(const FVector& A, const FVector& B);

	/**
	 * Gets the result of component-wise addition of this and another vector.
	 *
	 * @param V The vector to add to this.
	 * @return The result of vector addition.
	 */
	inline FVector operator+(const FVector& V) const;

	/**
	 * Gets the result of component-wise subtraction of this by another vector.
	 *
	 * @param V The vector to subtract from this.
	 * @return The result of vector subtraction.
	 */
	inline FVector operator-(const FVector& V) const;

	/**
	 * Gets the result of subtracting from each component of the vector.
	 *
	 * @param Bias How much to subtract from each component.
	 * @return The result of subtraction.
	 */
	inline FVector operator-(float Bias) const;

	/**
	 * Gets the result of adding to each component of the vector.
	 *
	 * @param Bias How much to add to each component.
	 * @return The result of addition.
	 */
	inline FVector operator+(float Bias) const;

	/**
	 * Gets the result of scaling the vector (multiplying each component by a value).
	 *
	 * @param Scale What to multiply each component by.
	 * @return The result of multiplication.
	 */
	inline FVector operator*(float Scale) const;

	/**
	 * Gets the result of dividing each component of the vector by a value.
	 *
	 * @param Scale What to divide each component by.
	 * @return The result of division.
	 */
	FVector operator/(float Scale) const;

	/**
	 * Gets the result of component-wise multiplication of this vector by another.
	 *
	 * @param V The vector to multiply with.
	 * @return The result of multiplication.
	 */
	inline FVector operator*(const FVector& V) const;

	/**
	 * Gets the result of component-wise division of this vector by another.
	 *
	 * @param V The vector to divide by.
	 * @return The result of division.
	 */
	inline FVector operator/(const FVector& V) const;

	// Binary comparison operators.

	/**
	 * Check against another vector for equality.
	 *
	 * @param V The vector to check against.
	 * @return true if the vectors are equal, false otherwise.
	 */
	bool operator==(const FVector& V) const;

	/**
	 * Check against another vector for inequality.
	 *
	 * @param V The vector to check against.
	 * @return true if the vectors are not equal, false otherwise.
	 */
	bool operator!=(const FVector& V) const;

	/**
	 * Check against another vector for equality, within specified error limits.
	 *
	 * @param V The vector to check against.
	 * @param Tolerance Error tolerance.
	 * @return true if the vectors are equal within tolerance limits, false otherwise.
	 */
	bool Equals(const FVector& V, float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	 * Checks whether all components of this vector are the same, within a tolerance.
	 *
	 * @param Tolerance Error tolerance.
	 * @return true if the vectors are equal within tolerance limits, false otherwise.
	 */
	bool AllComponentsEqual(float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	 * Get a negated copy of the vector.
	 *
	 * @return A negated copy of the vector.
	 */
	inline FVector operator-() const;

	/**
	 * Adds another vector to this.
	 * Uses component-wise addition.
	 *
	 * @param V Vector to add to this.
	 * @return Copy of the vector after addition.
	 */
	inline FVector operator+=(const FVector& V);

	/**
	 * Subtracts another vector from this.
	 * Uses component-wise subtraction.
	 *
	 * @param V Vector to subtract from this.
	 * @return Copy of the vector after subtraction.
	 */
	inline FVector operator-=(const FVector& V);

	/**
	 * Scales the vector.
	 *
	 * @param Scale Amount to scale this vector by.
	 * @return Copy of the vector after scaling.
	 */
	inline FVector operator*=(float Scale);

	/**
	 * Divides the vector by a number.
	 *
	 * @param V What to divide this vector by.
	 * @return Copy of the vector after division.
	 */
	FVector operator/=(float V);

	/**
	 * Multiplies the vector with another vector, using component-wise multiplication.
	 *
	 * @param V What to multiply this vector with.
	 * @return Copy of the vector after multiplication.
	 */
	FVector operator*=(const FVector& V);

	/**
	 * Divides the vector by another vector, using component-wise division.
	 *
	 * @param V What to divide vector by.
	 * @return Copy of the vector after division.
	 */
	FVector operator/=(const FVector& V);

	/**
	 * Gets specific component of the vector.
	 *
	 * @param Index the index of vector component
	 * @return reference to component.
	 */
	float& operator[](int Index);

	/**
	 * Gets specific component of the vector.
	 *
	 * @param Index the index of vector component
	 * @return Copy of the component.
	 */
	float operator[](int Index)const;

	/**
	* Gets a specific component of the vector.
	*
	* @param Index The index of the component required.
	*
	* @return Reference to the specified component.
	*/
	float& Component(int Index);

	/**
	* Gets a specific component of the vector.
	*
	* @param Index The index of the component required.
	* @return Copy of the specified component.
	*/
	float Component(int Index) const;

public:

	// Simple functions.

	/**
	 * Set the values of the vector directly.
	 *
	 * @param InX New X coordinate.
	 * @param InY New Y coordinate.
	 * @param InZ New Z coordinate.
	 */
	void Set(float InX, float InY, float InZ);

	/**
	 * Get the maximum value of the vector's components.
	 *
	 * @return The maximum value of the vector's components.
	 */
	float GetMax() const;

	/**
	 * Get the maximum absolute value of the vector's components.
	 *
	 * @return The maximum absolute value of the vector's components.
	 */
	float GetAbsMax() const;

	/**
	 * Get the minimum value of the vector's components.
	 *
	 * @return The minimum value of the vector's components.
	 */
	float GetMin() const;

	/**
	 * Get the minimum absolute value of the vector's components.
	 *
	 * @return The minimum absolute value of the vector's components.
	 */
	float GetAbsMin() const;

	/** Gets the component-wise min of two vectors. */
	FVector ComponentMin(const FVector& Other) const;

	/** Gets the component-wise max of two vectors. */
	FVector ComponentMax(const FVector& Other) const;

	/**
	 * Get a copy of this vector with absolute value of each component.
	 *
	 * @return A copy of this vector with absolute value of each component.
	 */
	FVector GetAbs() const;

	/**
	 * Get the length (magnitude) of this vector.
	 *
	 * @return The length of this vector.
	 */
	float Size() const;

	/**
	 * Get the squared length of this vector.
	 *
	 * @return The squared length of this vector.
	 */
	float SizeSquared() const;

	/**
	 * Get the length of the 2D components of this vector.
	 *
	 * @return The 2D length of this vector.
	 */
	float Size2D() const;

	/**
	 * Get the squared length of the 2D components of this vector.
	 *
	 * @return The squared 2D length of this vector.
	 */
	float SizeSquared2D() const;

	/**
	 * Checks whether vector is near to zero within a specified tolerance.
	 *
	 * @param Tolerance Error tolerance.
	 * @return true if the vector is near to zero, false otherwise.
	 */
	bool IsNearlyZero(float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	 * Checks whether all components of the vector are exactly zero.
	 *
	 * @return true if the vector is exactly zero, false otherwise.
	 */
	bool IsZero() const;

	/**
	 * Check if the vector is of unit length, with specified tolerance.
	 *
	 * @param LengthSquaredTolerance Tolerance against squared length.
	 * @return true if the vector is a unit vector within the specified tolerance.
	 */
	inline bool IsUnit(float LengthSquaredTolerance = KINDA_SMALL_NUMBER) const;

	/**
	 * Checks whether vector is normalized.
	 *
	 * @return true if normalized, false otherwise.
	 */
	bool IsNormalized() const;

	/**
	 * Normalize this vector in-place if it is larger than a given tolerance. Leaves it unchanged if not.
	 *
	 * @param Tolerance Minimum squared length of vector for normalization.
	 * @return true if the vector was normalized correctly, false otherwise.
	 */
	bool Normalize(float Tolerance = SMALL_NUMBER);

	/**
	 * Calculates normalized version of vector without checking for zero length.
	 *
	 * @return Normalized version of vector.
	 * @see GetSafeNormal()
	 */
	inline FVector GetUnsafeNormal() const;

	/**
	 * Gets a normalized copy of the vector, checking it is safe to do so based on the length.
	 * Returns zero vector if vector length is too small to safely normalize.
	 *
	 * @param Tolerance Minimum squared vector length.
	 * @return A normalized copy if safe, (0,0,0) otherwise.
	 */
	FVector GetSafeNormal(float Tolerance = SMALL_NUMBER) const;

	/**
	 * Gets a normalized copy of the 2D components of the vector, checking it is safe to do so. Z is set to zero.
	 * Returns zero vector if vector length is too small to normalize.
	 *
	 * @param Tolerance Minimum squared vector length.
	 * @return Normalized copy if safe, otherwise returns zero vector.
	 */
	FVector GetSafeNormal2D(float Tolerance = SMALL_NUMBER) const;

	/**
	 * Util to convert this vector into a unit direction vector and its original length.
	 *
	 * @param OutDir Reference passed in to store unit direction vector.
	 * @param OutLength Reference passed in to store length of the vector.
	 */
	void ToDirectionAndLength(FVector& OutDir, float& OutLength) const;

	/**
	 * Get a copy of the vector as sign only.
	 * Each component is set to +1 or -1, with the sign of zero treated as +1.
	 *
	 * @param A copy of the vector with each component set to +1 or -1
	 */
	inline FVector GetSignVector() const;

	/**
	 * Projects 2D components of vector based on Z.
	 *
	 * @return Projected version of vector based on Z.
	 */
	FVector Projection() const;

	/**
	* Calculates normalized 2D version of vector without checking for zero length.
	*
	* @return Normalized version of vector.
	* @see GetSafeNormal2D()
	*/
	inline FVector GetUnsafeNormal2D() const;

	/**
	 * Gets a copy of this vector snapped to a grid.
	 *
	 * @param GridSz Grid dimension.
	 * @return A copy of this vector snapped to a grid.
	 * @see FMath::GridSnap()
	 */
	FVector GridSnap(const float& GridSz) const;

	/**
	 * Get a copy of this vector, clamped inside of a cube.
	 *
	 * @param Radius Half size of the cube.
	 * @return A copy of this vector, bound by cube.
	 */
	FVector BoundToCube(float Radius) const;

	/** Get a copy of this vector, clamped inside of a cube. */
	FVector BoundToBox(const FVector& Min, const FVector Max) const;

	/** Create a copy of this vector, with its magnitude clamped between Min and Max. */
	FVector GetClampedToSize(float Min, float Max) const;

	/** Create a copy of this vector, with the 2D magnitude clamped between Min and Max. Z is unchanged. */
	FVector GetClampedToSize2D(float Min, float Max) const;

	/** Create a copy of this vector, with its maximum magnitude clamped to MaxSize. */
	FVector GetClampedToMaxSize(float MaxSize) const;

	/** Create a copy of this vector, with the maximum 2D magnitude clamped to MaxSize. Z is unchanged. */
	FVector GetClampedToMaxSize2D(float MaxSize) const;

	/**
	 * Gets the reciprocal of this vector, avoiding division by zero.
	 * Zero components are set to BIG_NUMBER.
	 *
	 * @return Reciprocal of this vector.
	 */
	FVector Reciprocal() const;

	/**
	 * Check whether X, Y and Z are nearly equal.
	 *
	 * @param Tolerance Specified Tolerance.
	 * @return true if X == Y == Z within the specified tolerance.
	 */
	bool IsUniform(float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	 * Mirror a vector about a normal vector.
	 *
	 * @param MirrorNormal Normal vector to mirror about.
	 * @return Mirrored vector.
	 */
	FVector MirrorByVector(const FVector& MirrorNormal) const;

	/**
	 * Mirrors a vector about a plane.
	 *
	 * @param Plane Plane to mirror about.
	 * @return Mirrored vector.
	 */
	FVector MirrorByPlane(const FPlane& Plane) const;

	/**
	 * Rotates around Axis (assumes Axis.Size() == 1).
	 *
	 * @param Angle Angle to rotate (in degrees).
	 * @param Axis Axis to rotate around.
	 * @return Rotated Vector.
	 */
	FVector RotateAngleAxis(const float AngleDeg, const FVector& Axis) const;

	/**
	 * Returns the cosine of the angle between this vector and another projected onto the XY plane (no Z).
	 *
	 * @param B the other vector to find the 2D cosine of the angle with.
	 * @return The cosine.
	 */
	inline float CosineAngle2D(FVector B) const;

	/**
	 * Gets a copy of this vector projected onto the input vector.
	 *
	 * @param A	Vector to project onto, does not assume it is normalized.
	 * @return Projected vector.
	 */
	inline FVector ProjectOnTo(const FVector& A) const;

	/**
	 * Gets a copy of this vector projected onto the input vector, which is assumed to be unit length.
	 *
	 * @param  Normal Vector to project onto (assumed to be unit length).
	 * @return Projected vector.
	 */
	inline FVector ProjectOnToNormal(const FVector& Normal) const;

	/**
	 * Convert a direction vector into a 'heading' angle.
	 *
	 * @return 'Heading' angle between +/-PI. 0 is pointing down +X.
	 */
	float HeadingAngle() const;

	/**
	 * Compare two points and see if they're the same, using a threshold.
	 *
	 * @param P First vector.
	 * @param Q Second vector.
	 * @return Whether points are the same within a threshold. Uses fast distance approximation (linear per-component distance).
	 */
	static bool PointsAreSame(const FVector& P, const FVector& Q);

	/**
	 * Compare two points and see if they're within specified distance.
	 *
	 * @param Point1 First vector.
	 * @param Point2 Second vector.
	 * @param Dist Specified distance.
	 * @return Whether two points are within the specified distance. Uses fast distance approximation (linear per-component distance).
	 */
	static bool PointsAreNear(const FVector& Point1, const FVector& Point2, float Dist);

	/**
	 * Calculate the signed distance (in the direction of the normal) between a point and a plane.
	 *
	 * @param Point The Point we are checking.
	 * @param PlaneBase The Base Point in the plane.
	 * @param PlaneNormal The Normal of the plane (assumed to be unit length).
	 * @return Signed distance between point and plane.
	 */
	static float PointPlaneDist(const FVector& Point, const FVector& PlaneBase, const FVector& PlaneNormal);

	/**
	 * Calculate the projection of a point on the given plane.
	 *
	 * @param Point The point to project onto the plane
	 * @param Plane The plane
	 * @return Projection of Point onto Plane
	 */
	static FVector PointPlaneProject(const FVector& Point, const FPlane& Plane);

	/**
	 * Calculate the projection of a point on the plane defined by counter-clockwise (CCW) points A,B,C.
	 *
	 * @param Point The point to project onto the plane
	 * @param A 1st of three points in CCW order defining the plane
	 * @param B 2nd of three points in CCW order defining the plane
	 * @param C 3rd of three points in CCW order defining the plane
	 * @return Projection of Point onto plane ABC
	 */
	static FVector PointPlaneProject(const FVector& Point, const FVector& A, const FVector& B, const FVector& C);

	/**
	* Calculate the projection of a point on the plane defined by PlaneBase and PlaneNormal.
	*
	* @param Point The point to project onto the plane
	* @param PlaneBase Point on the plane
	* @param PlaneNorm Normal of the plane (assumed to be unit length).
	* @return Projection of Point onto plane
	*/
	static FVector PointPlaneProject(const FVector& Point, const FVector& PlaneBase, const FVector& PlaneNormal);

	/**
	 * Calculate the projection of a vector on the plane defined by PlaneNormal.
	 *
	 * @param  V The vector to project onto the plane.
	 * @param  PlaneNormal Normal of the plane (assumed to be unit length).
	 * @return Projection of V onto plane.
	 */
	static FVector VectorPlaneProject(const FVector& V, const FVector& PlaneNormal);

	/**
	 * Euclidean distance between two points.
	 *
	 * @param V1 The first point.
	 * @param V2 The second point.
	 * @return The distance between two points.
	 */
	static inline float Dist(const FVector& V1, const FVector& V2);
	static inline float Distance(const FVector& V1, const FVector& V2) { return Dist(V1, V2); }

	/**
	* Euclidean distance between two points in the XY plane (ignoring Z).
	*
	* @param V1 The first point.
	* @param V2 The second point.
	* @return The distance between two points in the XY plane.
	*/
	static inline float DistXY(const FVector& V1, const FVector& V2);
	static inline float Dist2D(const FVector& V1, const FVector& V2) { return DistXY(V1, V2); }

	/**
	 * Squared distance between two points.
	 *
	 * @param V1 The first point.
	 * @param V2 The second point.
	 * @return The squared distance between two points.
	 */
	static inline float DistSquared(const FVector& V1, const FVector& V2);

	/**
	 * Squared distance between two points in the XY plane only.
	 *
	 * @param V1 The first point.
	 * @param V2 The second point.
	 * @return The squared distance between two points in the XY plane
	 */
	static inline float DistSquaredXY(const FVector& V1, const FVector& V2);
	static inline float DistSquared2D(const FVector& V1, const FVector& V2) { return DistSquaredXY(V1, V2); }

	/**
	 * Compute pushout of a box from a plane.
	 *
	 * @param Normal The plane normal.
	 * @param Size The size of the box.
	 * @return Pushout required.
	 */
	static inline float BoxPushOut(const FVector& Normal, const FVector& Size);

	/**
	 * See if two normal vectors are nearly parallel, meaning the angle between them is close to 0 degrees.
	 *
	 * @param  Normal1 First normalized vector.
	 * @param  Normal1 Second normalized vector.
	 * @param  ParallelCosineThreshold Normals are parallel if absolute value of dot product (cosine of angle between them) is greater than or equal to this. For example: cos(1.0 degrees).
	 * @return true if vectors are nearly parallel, false otherwise.
	 */
	static bool Parallel(const FVector& Normal1, const FVector& Normal2, float ParallelCosineThreshold = THRESH_NORMALS_ARE_PARALLEL);

	/**
	 * See if two normal vectors are coincident (nearly parallel and point in the same direction).
	 *
	 * @param  Normal1 First normalized vector.
	 * @param  Normal2 Second normalized vector.
	 * @param  ParallelCosineThreshold Normals are coincident if dot product (cosine of angle between them) is greater than or equal to this. For example: cos(1.0 degrees).
	 * @return true if vectors are coincident (nearly parallel and point in the same direction), false otherwise.
	 */
	static bool Coincident(const FVector& Normal1, const FVector& Normal2, float ParallelCosineThreshold = THRESH_NORMALS_ARE_PARALLEL);

	/**
	 * See if two normal vectors are nearly orthogonal (perpendicular), meaning the angle between them is close to 90 degrees.
	 *
	 * @param  Normal1 First normalized vector.
	 * @param  Normal2 Second normalized vector.
	 * @param  OrthogonalCosineThreshold Normals are orthogonal if absolute value of dot product (cosine of angle between them) is less than or equal to this. For example: cos(89.0 degrees).
	 * @return true if vectors are orthogonal (perpendicular), false otherwise.
	 */
	static bool Orthogonal(const FVector& Normal1, const FVector& Normal2, float OrthogonalCosineThreshold = THRESH_NORMALS_ARE_ORTHOGONAL);

	/**
	 * See if two planes are coplanar. They are coplanar if the normals are nearly parallel and the planes include the same set of points.
	 *
	 * @param Base1 The base point in the first plane.
	 * @param Normal1 The normal of the first plane.
	 * @param Base2 The base point in the second plane.
	 * @param Normal2 The normal of the second plane.
	 * @param ParallelCosineThreshold Normals are parallel if absolute value of dot product is greater than or equal to this.
	 * @return true if the planes are coplanar, false otherwise.
	 */
	static bool Coplanar(const FVector& Base1, const FVector& Normal1, const FVector& Base2, const FVector& Normal2, float ParallelCosineThreshold = THRESH_NORMALS_ARE_PARALLEL);

	/**
	 * Triple product of three vectors: X dot (Y cross Z).
	 *
	 * @param X The first vector.
	 * @param Y The second vector.
	 * @param Z The third vector.
	 * @return The triple product: X dot (Y cross Z).
	 */
	static float Triple(const FVector& X, const FVector& Y, const FVector& Z);

	/**
	 * Converts a vector containing radian values to a vector containing degree values.
	 *
	 * @param RadVector	Vector containing radian values
	 * @return Vector  containing degree values
	 */
	static FVector RadiansToDegrees(const FVector& RadVector);

	/**
	 * Converts a vector containing degree values to a vector containing radian values.
	 *
	 * @param DegVector	Vector containing degree values
	 * @return Vector containing radian values
	 */
	static FVector DegreesToRadians(const FVector& DegVector);
};

/* FVector inline functions
 *****************************************************************************/

 /**
  * Multiplies a vector by a scaling factor.
  *
  * @param Scale Scaling factor.
  * @param V Vector to scale.
  * @return Result of multiplication.
  */
inline FVector operator*(float Scale, const FVector& V)
{
	return V.operator*(Scale);
}

/**
 * Util to calculate distance from a point to a bounding box
 *
 * @param Mins 3D Point defining the lower values of the axis of the bound box
 * @param Max 3D Point defining the lower values of the axis of the bound box
 * @param Point 3D position of interest
 * @return the distance from the Point to the bounding box.
 */
inline float ComputeSquaredDistanceFromBoxToPoint(const FVector& Mins, const FVector& Maxs, const FVector& Point)
{
	// Accumulates the distance as we iterate axis
	float DistSquared = 0.f;

	// Check each axis for min/max and add the distance accordingly
	// NOTE: Loop manually unrolled for > 2x speed up
	if (Point.X < Mins.X)
	{
		DistSquared += FMath::Square(Point.X - Mins.X);
	}
	else if (Point.X > Maxs.X)
	{
		DistSquared += FMath::Square(Point.X - Maxs.X);
	}

	if (Point.Y < Mins.Y)
	{
		DistSquared += FMath::Square(Point.Y - Mins.Y);
	}
	else if (Point.Y > Maxs.Y)
	{
		DistSquared += FMath::Square(Point.Y - Maxs.Y);
	}

	if (Point.Z < Mins.Z)
	{
		DistSquared += FMath::Square(Point.Z - Mins.Z);
	}
	else if (Point.Z > Maxs.Z)
	{
		DistSquared += FMath::Square(Point.Z - Maxs.Z);
	}

	return DistSquared;
}


inline FVector::FVector(const FVector2D V, float InZ)
	: X(V.X), Y(V.Y), Z(InZ)
{

}

inline FVector FVector::RotateAngleAxis(const float AngleDeg, const FVector& Axis) const
{
	float S, C;
	FMath::SinCos(&S, &C, FMath::DegreesToRadians(AngleDeg));

	const float XX = Axis.X * Axis.X;
	const float YY = Axis.Y * Axis.Y;
	const float ZZ = Axis.Z * Axis.Z;

	const float XY = Axis.X * Axis.Y;
	const float YZ = Axis.Y * Axis.Z;
	const float ZX = Axis.Z * Axis.X;

	const float XS = Axis.X * S;
	const float YS = Axis.Y * S;
	const float ZS = Axis.Z * S;

	const float OMC = 1.f - C;

	return FVector(
		(OMC * XX + C) * X + (OMC * XY - ZS) * Y + (OMC * ZX + YS) * Z,
		(OMC * XY + ZS) * X + (OMC * YY + C) * Y + (OMC * YZ - XS) * Z,
		(OMC * ZX - YS) * X + (OMC * YZ + XS) * Y + (OMC * ZZ + C) * Z
	);
}

inline bool FVector::PointsAreSame(const FVector& P, const FVector& Q)
{
	float Temp;
	Temp = P.X - Q.X;
	if ((Temp > -THRESH_POINTS_ARE_SAME) && (Temp < THRESH_POINTS_ARE_SAME))
	{
		Temp = P.Y - Q.Y;
		if ((Temp > -THRESH_POINTS_ARE_SAME) && (Temp < THRESH_POINTS_ARE_SAME))
		{
			Temp = P.Z - Q.Z;
			if ((Temp > -THRESH_POINTS_ARE_SAME) && (Temp < THRESH_POINTS_ARE_SAME))
			{
				return true;
			}
		}
	}
	return false;
}

inline bool FVector::PointsAreNear(const FVector& Point1, const FVector& Point2, float Dist)
{
	float Temp;
	Temp = (Point1.X - Point2.X); if (std::abs(Temp) >= Dist) return false;
	Temp = (Point1.Y - Point2.Y); if (std::abs(Temp) >= Dist) return false;
	Temp = (Point1.Z - Point2.Z); if (std::abs(Temp) >= Dist) return false;
	return true;
}

inline float FVector::PointPlaneDist
(
	const FVector& Point,
	const FVector& PlaneBase,
	const FVector& PlaneNormal
)
{
	return (Point - PlaneBase) | PlaneNormal;
}


inline FVector FVector::PointPlaneProject(const FVector& Point, const FVector& PlaneBase, const FVector& PlaneNorm)
{
	//Find the distance of X from the plane
	//Add the distance back along the normal from the point
	return Point - FVector::PointPlaneDist(Point, PlaneBase, PlaneNorm) * PlaneNorm;
}

inline FVector FVector::VectorPlaneProject(const FVector& V, const FVector& PlaneNormal)
{
	return V - V.ProjectOnToNormal(PlaneNormal);
}

inline bool FVector::Parallel(const FVector& Normal1, const FVector& Normal2, float ParallelCosineThreshold)
{
	const float NormalDot = Normal1 | Normal2;
	return std::abs(NormalDot) >= ParallelCosineThreshold;
}

inline bool FVector::Coincident(const FVector& Normal1, const FVector& Normal2, float ParallelCosineThreshold)
{
	const float NormalDot = Normal1 | Normal2;
	return NormalDot >= ParallelCosineThreshold;
}

inline bool FVector::Orthogonal(const FVector& Normal1, const FVector& Normal2, float OrthogonalCosineThreshold)
{
	const float NormalDot = Normal1 | Normal2;
	return std::abs(NormalDot) <= OrthogonalCosineThreshold;
}

inline bool FVector::Coplanar(const FVector& Base1, const FVector& Normal1, const FVector& Base2, const FVector& Normal2, float ParallelCosineThreshold)
{
	if (!FVector::Parallel(Normal1, Normal2, ParallelCosineThreshold)) return false;
	else if (std::abs(FVector::PointPlaneDist(Base2, Base1, Normal1)) > THRESH_POINT_ON_PLANE) return false;
	else return true;
}

inline float FVector::Triple(const FVector& X, const FVector& Y, const FVector& Z)
{
	return
		((X.X * (Y.Y * Z.Z - Y.Z * Z.Y))
			+ (X.Y * (Y.Z * Z.X - Y.X * Z.Z))
			+ (X.Z * (Y.X * Z.Y - Y.Y * Z.X)));
}

inline FVector FVector::RadiansToDegrees(const FVector& RadVector)
{
	return RadVector * (180.f / PI);
}

inline FVector FVector::DegreesToRadians(const FVector& DegVector)
{
	return DegVector * (PI / 180.f);
}

inline FVector::FVector() : X(0.0f), Y(0.0f), Z(0.0f)
{

}

inline FVector::FVector(float InF)
	: X(InF), Y(InF), Z(InF)
{

}

inline FVector::FVector(float InX, float InY, float InZ)
	: X(InX), Y(InY), Z(InZ)
{

}

inline FVector::FVector(FIntPoint A)
	: X((float)A.X), Y((float)A.Y), Z(0.f)
{

}

inline FVector& FVector::operator=(const FVector& Other)
{
	this->X = Other.X;
	this->Y = Other.Y;
	this->Z = Other.Z;
	return *this;
}

inline FVector FVector::operator^(const FVector& V) const
{
	return FVector
	(
		Y * V.Z - Z * V.Y,
		Z * V.X - X * V.Z,
		X * V.Y - Y * V.X
	);
}

inline FVector FVector::CrossProduct(const FVector& A, const FVector& B)
{
	return A ^ B;
}

inline float FVector::operator|(const FVector& V) const
{
	return X * V.X + Y * V.Y + Z * V.Z;
}

inline float FVector::DotProduct(const FVector& A, const FVector& B)
{
	return A | B;
}

inline FVector FVector::operator+(const FVector& V) const
{
	return FVector(X + V.X, Y + V.Y, Z + V.Z);
}

inline FVector FVector::operator-(const FVector& V) const
{
	return FVector(X - V.X, Y - V.Y, Z - V.Z);
}

inline FVector FVector::operator-(float Bias) const
{
	return FVector(X - Bias, Y - Bias, Z - Bias);
}

inline FVector FVector::operator+(float Bias) const
{
	return FVector(X + Bias, Y + Bias, Z + Bias);
}

inline FVector FVector::operator*(float Scale) const
{
	return FVector(X * Scale, Y * Scale, Z * Scale);
}

inline FVector FVector::operator/(float Scale) const
{
	const float RScale = 1.f / Scale;
	return FVector(X * RScale, Y * RScale, Z * RScale);
}

inline FVector FVector::operator*(const FVector& V) const
{
	return FVector(X * V.X, Y * V.Y, Z * V.Z);
}

inline FVector FVector::operator/(const FVector& V) const
{
	return FVector(X / V.X, Y / V.Y, Z / V.Z);
}

inline bool FVector::operator==(const FVector& V) const
{
	return X == V.X && Y == V.Y && Z == V.Z;
}

inline bool FVector::operator!=(const FVector& V) const
{
	return X != V.X || Y != V.Y || Z != V.Z;
}

inline bool FVector::Equals(const FVector& V, float Tolerance) const
{
	return std::abs(X - V.X) <= Tolerance && std::abs(Y - V.Y) <= Tolerance && std::abs(Z - V.Z) <= Tolerance;
}

inline bool FVector::AllComponentsEqual(float Tolerance) const
{
	return std::abs(X - Y) <= Tolerance && std::abs(X - Z) <= Tolerance && std::abs(Y - Z) <= Tolerance;
}


inline FVector FVector::operator-() const
{
	return FVector(-X, -Y, -Z);
}


inline FVector FVector::operator+=(const FVector& V)
{
	X += V.X; Y += V.Y; Z += V.Z;

	return *this;
}

inline FVector FVector::operator-=(const FVector& V)
{
	X -= V.X; Y -= V.Y; Z -= V.Z;

	return *this;
}

inline FVector FVector::operator*=(float Scale)
{
	X *= Scale; Y *= Scale; Z *= Scale;

	return *this;
}

inline FVector FVector::operator/=(float V)
{
	const float RV = 1.f / V;
	X *= RV; Y *= RV; Z *= RV;

	return *this;
}

inline FVector FVector::operator*=(const FVector& V)
{
	X *= V.X; Y *= V.Y; Z *= V.Z;

	return *this;
}

inline FVector FVector::operator/=(const FVector& V)
{
	X /= V.X; Y /= V.Y; Z /= V.Z;

	return *this;
}

inline float& FVector::operator[](int Index)
{
	return (&X)[Index];
}

inline float FVector::operator[](int Index)const
{
	return (&X)[Index];
}

inline void FVector::Set(float InX, float InY, float InZ)
{
	X = InX;
	Y = InY;
	Z = InZ;

}

inline float FVector::GetMax() const
{
	return MAX(MAX(X, Y), Z);
}

inline float FVector::GetAbsMax() const
{
	return MAX(MAX(std::abs(X), std::abs(Y)), std::abs(Z));
}

inline float FVector::GetMin() const
{
	return MIN(MIN(X, Y), Z);
}

inline float FVector::GetAbsMin() const
{
	return MIN(MIN(std::abs(X), std::abs(Y)), std::abs(Z));
}

inline FVector FVector::ComponentMin(const FVector& Other) const
{
	return FVector(MIN(X, Other.X), MIN(Y, Other.Y), MIN(Z, Other.Z));
}

inline FVector FVector::ComponentMax(const FVector& Other) const
{
	return FVector(MAX(X, Other.X), MAX(Y, Other.Y), MAX(Z, Other.Z));
}

inline FVector FVector::GetAbs() const
{
	return FVector(std::abs(X), std::abs(Y), std::abs(Z));
}

inline float FVector::Size() const
{
	return std::sqrt(X * X + Y * Y + Z * Z);
}

inline float FVector::SizeSquared() const
{
	return X * X + Y * Y + Z * Z;
}

inline float FVector::Size2D() const
{
	return std::sqrt(X * X + Y * Y);
}

inline float FVector::SizeSquared2D() const
{
	return X * X + Y * Y;
}

inline bool FVector::IsNearlyZero(float Tolerance) const
{
	return
		std::abs(X) <= Tolerance
		&& std::abs(Y) <= Tolerance
		&& std::abs(Z) <= Tolerance;
}

inline bool FVector::IsZero() const
{
	return X == 0.f && Y == 0.f && Z == 0.f;
}

inline bool FVector::Normalize(float Tolerance)
{
	const float SquareSum = X * X + Y * Y + Z * Z;
	if (SquareSum > Tolerance)
	{
		const float Scale = FMath::InvSqrt(SquareSum);
		X *= Scale; Y *= Scale; Z *= Scale;
		return true;
	}
	return false;
}

inline bool FVector::IsUnit(float LengthSquaredTolerance) const
{
	return std::abs(1.0f - SizeSquared()) < LengthSquaredTolerance;
}

inline bool FVector::IsNormalized() const
{
	return (std::abs(1.f - SizeSquared()) < THRESH_VECTOR_NORMALIZED);
}

inline void FVector::ToDirectionAndLength(FVector& OutDir, float& OutLength) const
{
	OutLength = Size();
	if (OutLength > SMALL_NUMBER)
	{
		float OneOverLength = 1.0f / OutLength;
		OutDir = FVector(X * OneOverLength, Y * OneOverLength,
			Z * OneOverLength);
	}
	else
	{
		OutDir = FVector::ZeroVector;
	}
}

inline FVector FVector::GetSignVector() const
{
	return FVector
	(
		FMath::FloatSelect(X, 1.f, -1.f),
		FMath::FloatSelect(Y, 1.f, -1.f),
		FMath::FloatSelect(Z, 1.f, -1.f)
	);
}

inline FVector FVector::Projection() const
{
	const float RZ = 1.f / Z;
	return FVector(X * RZ, Y * RZ, 1);
}

inline FVector FVector::GetUnsafeNormal() const
{
	const float Scale = FMath::InvSqrt(X * X + Y * Y + Z * Z);
	return FVector(X * Scale, Y * Scale, Z * Scale);
}

inline FVector FVector::GetUnsafeNormal2D() const
{
	const float Scale = FMath::InvSqrt(X * X + Y * Y);
	return FVector(X * Scale, Y * Scale, 0);
}

inline FVector FVector::GridSnap(const float& GridSz) const
{
	return FVector(FMath::GridSnap(X, GridSz), FMath::GridSnap(Y, GridSz), FMath::GridSnap(Z, GridSz));
}

inline FVector FVector::BoundToCube(float Radius) const
{
	return FVector
	(
		FMath::Clamp(X, -Radius, Radius),
		FMath::Clamp(Y, -Radius, Radius),
		FMath::Clamp(Z, -Radius, Radius)
	);
}

inline FVector FVector::BoundToBox(const FVector& Min, const FVector Max) const
{
	return FVector
	(
		FMath::Clamp(X, Min.X, Max.X),
		FMath::Clamp(Y, Min.Y, Max.Y),
		FMath::Clamp(Z, Min.Z, Max.Z)
	);
}


inline FVector FVector::GetClampedToSize(float Min, float Max) const
{
	float VecSize = Size();
	const FVector VecDir = (VecSize > SMALL_NUMBER) ? (*this / VecSize) : FVector::ZeroVector;

	VecSize = FMath::Clamp(VecSize, Min, Max);

	return VecSize * VecDir;
}

inline FVector FVector::GetClampedToSize2D(float Min, float Max) const
{
	float VecSize2D = Size2D();
	const FVector VecDir = (VecSize2D > SMALL_NUMBER) ? (*this / VecSize2D) : FVector::ZeroVector;

	VecSize2D = FMath::Clamp(VecSize2D, Min, Max);

	return FVector(VecSize2D * VecDir.X, VecSize2D * VecDir.Y, Z);
}

inline FVector FVector::GetClampedToMaxSize(float MaxSize) const
{
	if (MaxSize < KINDA_SMALL_NUMBER)
	{
		return FVector::ZeroVector;
	}

	const float VSq = SizeSquared();
	if (VSq > FMath::Square(MaxSize))
	{
		const float Scale = MaxSize * FMath::InvSqrt(VSq);
		return FVector(X * Scale, Y * Scale, Z * Scale);
	}
	else
	{
		return *this;
	}
}

inline FVector FVector::GetClampedToMaxSize2D(float MaxSize) const
{
	if (MaxSize < KINDA_SMALL_NUMBER)
	{
		return FVector::ZeroVector;
	}

	const float VSq2D = SizeSquared2D();
	if (VSq2D > FMath::Square(MaxSize))
	{
		const float Scale = MaxSize * FMath::InvSqrt(VSq2D);
		return FVector(X * Scale, Y * Scale, Z);
	}
	else
	{
		return *this;
	}
}

inline float& FVector::Component(int Index)
{
	return (&X)[Index];
}

inline float FVector::Component(int Index) const
{
	return (&X)[Index];
}

inline FVector FVector::Reciprocal() const
{
	FVector RecVector;
	if (X != 0.f)
	{
		RecVector.X = 1.f / X;
	}
	else
	{
		RecVector.X = BIG_NUMBER;
	}
	if (Y != 0.f)
	{
		RecVector.Y = 1.f / Y;
	}
	else
	{
		RecVector.Y = BIG_NUMBER;
	}
	if (Z != 0.f)
	{
		RecVector.Z = 1.f / Z;
	}
	else
	{
		RecVector.Z = BIG_NUMBER;
	}

	return RecVector;
}

inline bool FVector::IsUniform(float Tolerance) const
{
	return AllComponentsEqual(Tolerance);
}

inline FVector FVector::MirrorByVector(const FVector& MirrorNormal) const
{
	return *this - MirrorNormal * (2.f * (*this | MirrorNormal));
}

inline FVector FVector::GetSafeNormal(float Tolerance) const
{
	const float SquareSum = X * X + Y * Y + Z * Z;

	// Not sure if it's safe to add tolerance in there. Might introduce too many errors
	if (SquareSum == 1.f)
	{
		return *this;
	}
	else if (SquareSum < Tolerance)
	{
		return FVector::ZeroVector;
	}
	const float Scale = FMath::InvSqrt(SquareSum);
	return FVector(X * Scale, Y * Scale, Z * Scale);
}

inline FVector FVector::GetSafeNormal2D(float Tolerance) const
{
	const float SquareSum = X * X + Y * Y;

	// Not sure if it's safe to add tolerance in there. Might introduce too many errors
	if (SquareSum == 1.f)
	{
		if (Z == 0.f)
		{
			return *this;
		}
		else
		{
			return FVector(X, Y, 0.f);
		}
	}
	else if (SquareSum < Tolerance)
	{
		return FVector::ZeroVector;
	}

	const float Scale = FMath::InvSqrt(SquareSum);
	return FVector(X * Scale, Y * Scale, 0.f);
}

inline float FVector::CosineAngle2D(FVector B) const
{
	FVector A(*this);
	A.Z = 0.0f;
	B.Z = 0.0f;
	A.Normalize();
	B.Normalize();
	return A | B;
}

inline FVector FVector::ProjectOnTo(const FVector& A) const
{
	return (A * ((*this | A) / (A | A)));
}

inline FVector FVector::ProjectOnToNormal(const FVector& Normal) const
{
	return (Normal * (*this | Normal));
}


inline float FVector::HeadingAngle() const
{
	// Project Dir into Z plane.
	FVector PlaneDir = *this;
	PlaneDir.Z = 0.f;
	PlaneDir = PlaneDir.GetSafeNormal();

	float Angle = std::acos(PlaneDir.X);

	if (PlaneDir.Y < 0.0f)
	{
		Angle *= -1.0f;
	}

	return Angle;
}

inline float FVector::Dist(const FVector& V1, const FVector& V2)
{
	return std::sqrt(FVector::DistSquared(V1, V2));
}

inline float FVector::DistXY(const FVector& V1, const FVector& V2)
{
	return std::sqrt(FVector::DistSquaredXY(V1, V2));
}

inline float FVector::DistSquared(const FVector& V1, const FVector& V2)
{
	return FMath::Square(V2.X - V1.X) + FMath::Square(V2.Y - V1.Y) + FMath::Square(V2.Z - V1.Z);
}

inline float FVector::DistSquaredXY(const FVector& V1, const FVector& V2)
{
	return FMath::Square(V2.X - V1.X) + FMath::Square(V2.Y - V1.Y);
}

inline float FVector::BoxPushOut(const FVector& Normal, const FVector& Size)
{
	return std::abs(Normal.X * Size.X) + std::abs(Normal.Y * Size.Y) + std::abs(Normal.Z * Size.Z);
}

/** Component-wise clamp for FVector */
inline FVector ClampVector(const FVector& V, const FVector& Min, const FVector& Max)
{
	return FVector(
		FMath::Clamp(V.X, Min.X, Max.X),
		FMath::Clamp(V.Y, Min.Y, Max.Y),
		FMath::Clamp(V.Z, Min.Z, Max.Z)
	);
}

/* FVector2D inline functions
 *****************************************************************************/

inline FVector2D::FVector2D(const FVector& V)
	: X(V.X), Y(V.Y)
{

}

static const struct FVector ZeroVector = { 0.0f, 0.0f, 0.0f };
