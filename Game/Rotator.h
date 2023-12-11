// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UnrealMathUtility.h"
#include "Vector.h"

/**
 * Implements a container for rotation information.
 *
 * All rotation values are stored in degrees.
 */
struct FRotator
{
public:
	/** Rotation around the right axis (around Y axis), Looking up and down (0=Straight Ahead, +Up, -Down) */
	float Pitch;

	/** Rotation around the up axis (around Z axis), Running in circles 0=East, +North, -South. */
	float Yaw;

	/** Rotation around the forward axis (around X axis), Tilting your head, 0=Straight, +Clockwise, -CCW. */
	float Roll;

public:

	/** A rotator of zero degrees on each axis. */
	static const FRotator ZeroRotator;

public:

	/**
	 * Default constructor (no initialization).
	 */
	inline FRotator() : Pitch(0.0f), Yaw(0.0f), Roll(0.0f) {}

	/**
	 * Constructor
	 *
	 * @param InF Value to set all components to.
	 */
	explicit inline FRotator(float InF);

	/**
	 * Constructor.
	 *
	 * @param InPitch Pitch in degrees.
	 * @param InYaw Yaw in degrees.
	 * @param InRoll Roll in degrees.
	 */
	inline FRotator(float InPitch, float InYaw, float InRoll);;

public:

	// Binary arithmetic operators.

	/**
	 * Get the result of adding a rotator to this.
	 *
	 * @param R The other rotator.
	 * @return The result of adding a rotator to this.
	 */
	FRotator operator+(const FRotator& R) const;

	/**
	 * Get the result of subtracting a rotator from this.
	 *
	 * @param R The other rotator.
	 * @return The result of subtracting a rotator from this.
	 */
	FRotator operator-(const FRotator& R) const;

	/**
	 * Get the result of scaling this rotator.
	 *
	 * @param Scale The scaling factor.
	 * @return The result of scaling.
	 */
	FRotator operator*(float Scale) const;

	/**
	 * Multiply this rotator by a scaling factor.
	 *
	 * @param Scale The scaling factor.
	 * @return Copy of the rotator after scaling.
	 */
	FRotator operator*=(float Scale);

	// Binary comparison operators.

	/**
	 * Checks whether two rotators are identical. This checks each component for exact equality.
	 *
	 * @param R The other rotator.
	 * @return true if two rotators are identical, otherwise false.
	 * @see Equals()
	 */
	bool operator==(const FRotator& R) const;

	/**
	 * Checks whether two rotators are different.
	 *
	 * @param V The other rotator.
	 * @return true if two rotators are different, otherwise false.
	 */
	bool operator!=(const FRotator& V) const;

	// Assignment operators.

	/**
	 * Adds another rotator to this.
	 *
	 * @param R The other rotator.
	 * @return Copy of rotator after addition.
	 */
	FRotator operator+=(const FRotator& R);

	/**
	 * Subtracts another rotator from this.
	 *
	 * @param R The other rotator.
	 * @return Copy of rotator after subtraction.
	 */
	FRotator operator-=(const FRotator& R);

public:

	// Functions.

	/**
	 * Checks whether rotator is nearly zero within specified tolerance, when treated as an orientation.
	 * This means that FRotator(0, 0, 360) is "zero", because it is the same final orientation as the zero rotator.
	 *
	 * @param Tolerance Error Tolerance.
	 * @return true if rotator is nearly zero, within specified tolerance, otherwise false.
	 */
	bool IsNearlyZero(float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	 * Checks whether this has exactly zero rotation, when treated as an orientation.
	 * This means that FRotator(0, 0, 360) is "zero", because it is the same final orientation as the zero rotator.
	 *
	 * @return true if this has exactly zero rotation, otherwise false.
	 */
	bool IsZero() const;

	/**
	 * Checks whether two rotators are equal within specified tolerance, when treated as an orientation.
	 * This means that FRotator(0, 0, 360).Equals(FRotator(0,0,0)) is true, because they represent the same final orientation.
	 *
	 * @param R The other rotator.
	 * @param Tolerance Error Tolerance.
	 * @return true if two rotators are equal, within specified tolerance, otherwise false.
	 */
	bool Equals(const FRotator& R, float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	 * Adds to each component of the rotator.
	 *
	 * @param DeltaPitch Change in pitch. (+/-)
	 * @param DeltaYaw Change in yaw. (+/-)
	 * @param DeltaRoll Change in roll. (+/-)
	 * @return Copy of rotator after addition.
	 */
	FRotator Add(float DeltaPitch, float DeltaYaw, float DeltaRoll);

	/**
	 * Get the rotation, snapped to specified degree segments.
	 *
	 * @param RotGrid A Rotator specifying how to snap each component.
	 * @return Snapped version of rotation.
	 */
	FRotator GridSnap(const FRotator& RotGrid) const;

	/**
	 * Gets the rotation values so they fall within the range [0,360]
	 *
	 * @return Clamped version of rotator.
	 */
	FRotator Clamp() const;

	/**
	 * Create a copy of this rotator and normalize, removes all winding and creates the "shortest route" rotation.
	 *
	 * @return Normalized copy of this rotator
	 */
	FRotator GetNormalized() const;

	/**
	 * Create a copy of this rotator and denormalize, clamping each axis to 0 - 360.
	 *
	 * @return Denormalized copy of this rotator
	 */
	FRotator GetDenormalized() const;

	/**
	 * In-place normalize, removes all winding and creates the "shortest route" rotation.
	 */
	void Normalize();

	/**
	* Return a Rotator that has the same rotation but has different degree values for Yaw, Pitch, and Roll.
	* This rotator should be within -180,180 range,
	* @return A Rotator with the same rotation but different degrees.
	*/
	FRotator GetEquivalentRotator() const;
public:

	/**
	 * Clamps an angle to the range of [0, 360).
	 *
	 * @param Angle The angle to clamp.
	 * @return The clamped angle.
	 */
	static float ClampAxis(float Angle);

	/**
	 * Clamps an angle to the range of (-180, 180].
	 *
	 * @param Angle The Angle to clamp.
	 * @return The clamped angle.
	 */
	static float NormalizeAxis(float Angle);
};


/* FRotator inline functions
 *****************************************************************************/

 /**
  * Scale a rotator and return.
  *
  * @param Scale scale to apply to R.
  * @param R rotator to be scaled.
  * @return Scaled rotator.
  */
inline FRotator operator*(float Scale, const FRotator& R)
{
	return R.operator*(Scale);
}


inline FRotator::FRotator(float InF)
	: Pitch(InF), Yaw(InF), Roll(InF)
{

}


inline FRotator::FRotator(float InPitch, float InYaw, float InRoll)
	: Pitch(InPitch), Yaw(InYaw), Roll(InRoll)
{

}


inline FRotator FRotator::operator+(const FRotator& R) const
{
	return FRotator(Pitch + R.Pitch, Yaw + R.Yaw, Roll + R.Roll);
}


inline FRotator FRotator::operator-(const FRotator& R) const
{
	return FRotator(Pitch - R.Pitch, Yaw - R.Yaw, Roll - R.Roll);
}


inline FRotator FRotator::operator*(float Scale) const
{
	return FRotator(Pitch * Scale, Yaw * Scale, Roll * Scale);
}


inline FRotator FRotator::operator*= (float Scale)
{
	Pitch = Pitch * Scale; Yaw = Yaw * Scale; Roll = Roll * Scale;
	return *this;
}


inline bool FRotator::operator==(const FRotator& R) const
{
	return Pitch == R.Pitch && Yaw == R.Yaw && Roll == R.Roll;
}


inline bool FRotator::operator!=(const FRotator& V) const
{
	return Pitch != V.Pitch || Yaw != V.Yaw || Roll != V.Roll;
}


inline FRotator FRotator::operator+=(const FRotator& R)
{
	Pitch += R.Pitch; Yaw += R.Yaw; Roll += R.Roll;
	return *this;
}


inline FRotator FRotator::operator-=(const FRotator& R)
{
	Pitch -= R.Pitch; Yaw -= R.Yaw; Roll -= R.Roll;
	return *this;
}


inline bool FRotator::IsNearlyZero(float Tolerance) const
{
	return
		std::abs(NormalizeAxis(Pitch)) <= Tolerance
		&& std::abs(NormalizeAxis(Yaw)) <= Tolerance
		&& std::abs(NormalizeAxis(Roll)) <= Tolerance;
}


inline bool FRotator::IsZero() const
{
	return (ClampAxis(Pitch) == 0.f) && (ClampAxis(Yaw) == 0.f) && (ClampAxis(Roll) == 0.f);
}


inline bool FRotator::Equals(const FRotator& R, float Tolerance) const
{
	return (std::abs(NormalizeAxis(Pitch - R.Pitch)) <= Tolerance)
		&& (std::abs(NormalizeAxis(Yaw - R.Yaw)) <= Tolerance)
		&& (std::abs(NormalizeAxis(Roll - R.Roll)) <= Tolerance);
}


inline FRotator FRotator::Add(float DeltaPitch, float DeltaYaw, float DeltaRoll)
{
	Yaw += DeltaYaw;
	Pitch += DeltaPitch;
	Roll += DeltaRoll;
	return *this;
}


inline FRotator FRotator::GridSnap(const FRotator& RotGrid) const
{
	return FRotator
	(
		FMath::GridSnap(Pitch, RotGrid.Pitch),
		FMath::GridSnap(Yaw, RotGrid.Yaw),
		FMath::GridSnap(Roll, RotGrid.Roll)
	);
}


inline FRotator FRotator::Clamp() const
{
	return FRotator(ClampAxis(Pitch), ClampAxis(Yaw), ClampAxis(Roll));
}


inline float FRotator::ClampAxis(float Angle)
{
	// returns Angle in the range (-360,360)
	Angle = std::fmod(Angle, 360.f);

	if (Angle < 0.f)
	{
		// shift to [0,360) range
		Angle += 360.f;
	}

	return Angle;
}


inline float FRotator::NormalizeAxis(float Angle)
{
	// returns Angle in the range [0,360)
	Angle = ClampAxis(Angle);

	if (Angle > 180.f)
	{
		// shift to (-180,180]
		Angle -= 360.f;
	}

	return Angle;
}


inline FRotator FRotator::GetNormalized() const
{
	FRotator Rot = *this;
	Rot.Normalize();
	return Rot;
}


inline FRotator FRotator::GetDenormalized() const
{
	FRotator Rot = *this;
	Rot.Pitch = ClampAxis(Rot.Pitch);
	Rot.Yaw = ClampAxis(Rot.Yaw);
	Rot.Roll = ClampAxis(Rot.Roll);
	return Rot;
}


inline void FRotator::Normalize()
{
	Pitch = NormalizeAxis(Pitch);
	Yaw = NormalizeAxis(Yaw);
	Roll = NormalizeAxis(Roll);
}


inline FRotator FRotator::GetEquivalentRotator() const
{
	return FRotator(180.0f - Pitch, Yaw + 180.0f, Roll + 180.0f);
}

static const struct FRotator ZeroRotator = { 0.0f, 0.0f, 0.0f };

