// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UnrealMathUtility.h"
#include "Vector.h"
#include "Vector4.h"
#include "Plane.h"
#include "Rotator.h"

struct VectorRegister
{
	float	V[4];
};

/**
 * 4x4 matrix of floating point values.
 * Matrix-matrix multiplication happens with a pre-multiple of the transpose --
 * in other words, Res = Mat1.operator*(Mat2) means Res = Mat2^T * Mat1, as
 * opposed to Res = Mat1 * Mat2.
 * Matrix elements are accessed with M[RowIndex][ColumnIndex].
 */
struct FMatrix
{
public:
	float M[4][4];

	// Constructors.
	inline FMatrix();

	/**
	 * Constructor.
	 *
	 * @param InX X plane
	 * @param InY Y plane
	 * @param InZ Z plane
	 * @param InW W plane
	 */
	inline FMatrix(const FPlane& InX, const FPlane& InY, const FPlane& InZ, const FPlane& InW);

	/**
	 * Constructor.
	 *
	 * @param InX X vector
	 * @param InY Y vector
	 * @param InZ Z vector
	 * @param InW W vector
	 */
	inline FMatrix(const FVector& InX, const FVector& InY, const FVector& InZ, const FVector& InW);

	// Set this to the identity matrix
	inline void SetIdentity();

	/**
	 * Gets the result of multiplying a Matrix to this.
	 *
	 * @param Other The matrix to multiply this by.
	 * @return The result of multiplication.
	 */
	inline FMatrix operator*(const FMatrix& Other) const;

	/**
	 * Multiply this by a matrix.
	 *
	 * @param Other the matrix to multiply by this.
	 * @return reference to this after multiply.
	 */
	inline void operator*=(const FMatrix& Other);

	/**
	 * Gets the result of adding a matrix to this.
	 *
	 * @param Other The Matrix to add.
	 * @return The result of addition.
	 */
	inline FMatrix operator+ (const FMatrix& Other) const;

	/**
	 * Adds to this matrix.
	 *
	 * @param Other The matrix to add to this.
	 * @return Reference to this after addition.
	 */
	inline void operator+=(const FMatrix& Other);

	/**
	  * This isn't applying SCALE, just multiplying the value to all members - i.e. weighting
	  */
	inline FMatrix operator* (float Other) const;

	/**
	 * Multiply this matrix by a weighting factor.
	 *
	 * @param other The weight.
	 * @return a reference to this after weighting.
	 */
	inline void operator*=(float Other);

	/**
	 * Checks whether two matrix are identical.
	 *
	 * @param Other The other matrix.
	 * @return true if two matrix are identical, otherwise false.
	 */
	inline bool operator==(const FMatrix& Other) const;

	/**
	 * Checks whether another Matrix is equal to this, within specified tolerance.
	 *
	 * @param Other The other Matrix.
	 * @param Tolerance Error Tolerance.
	 * @return true if two Matrix are equal, within specified tolerance, otherwise false.
	 */
	inline bool Equals(const FMatrix& Other, float Tolerance = KINDA_SMALL_NUMBER) const;

	/**
	 * Checks whether another Matrix is not equal to this, within specified tolerance.
	 *
	 * @param Other The other Matrix.
	 * @return true if two Matrix are not equal, within specified tolerance, otherwise false.
	 */
	inline bool operator!=(const FMatrix& Other) const;

	// Homogeneous transform.
	inline FVector4 TransformFVector4(const FVector4& V) const;

	/** Transform a location - will take into account translation part of the FMatrix. */
	inline FVector4 TransformPosition(const FVector& V) const;

	/** Inverts the matrix and then transforms V - correctly handles scaling in this matrix. */
	inline FVector InverseTransformPosition(const FVector& V) const;

	/**
	 *	Transform a direction vector - will not take into account translation part of the FMatrix.
	 *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT.
	 */
	inline FVector4 TransformVector(const FVector& V) const;

	/**
	 *	Transform a direction vector by the inverse of this matrix - will not take into account translation part.
	 *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT with adjoint of matrix inverse.
	 */
	inline FVector InverseTransformVector(const FVector& V) const;

	// Transpose.

	inline FMatrix GetTransposed() const;

	// @return determinant of this matrix.

	inline float Determinant() const;

	/** @return the determinant of rotation 3x3 matrix */
	inline float RotDeterminant() const;

	/** Fast path, doesn't check for nil matrices in final release builds */
	inline FMatrix InverseFast() const;

	/** Fast path, and handles nil matrices. */
	inline FMatrix Inverse() const;

	inline FMatrix TransposeAdjoint() const;

	// NOTE: There is some compiler optimization issues with WIN64 that cause inline to cause a crash
	// Remove any scaling from this matrix (ie magnitude of each row is 1) with error Tolerance
	inline void RemoveScaling(float Tolerance = SMALL_NUMBER);

	// Returns matrix after RemoveScaling with error Tolerance
	inline FMatrix GetMatrixWithoutScale(float Tolerance = SMALL_NUMBER) const;

	/** Remove any scaling from this matrix (ie magnitude of each row is 1) and return the 3D scale vector that was initially present with error Tolerance */
	inline FVector ExtractScaling(float Tolerance = SMALL_NUMBER);

	/** return a 3D scale vector calculated from this matrix (where each component is the magnitude of a row vector) with error Tolerance. */
	inline FVector GetScaleVector(float Tolerance = SMALL_NUMBER) const;

	// Remove any translation from this matrix
	inline FMatrix RemoveTranslation() const;

	/** Returns a matrix with an additional translation concatenated. */
	inline FMatrix ConcatTranslation(const FVector& Translation) const;

	/** Returns true if any element of this matrix is NaN */
	inline bool ContainsNaN() const;

	/** Scale the translation part of the matrix by the supplied vector. */
	inline void ScaleTranslation(const FVector& Scale3D);

	/** @return the maximum magnitude of any row of the matrix. */
	inline float GetMaximumAxisScale() const;

	/** Apply Scale to this matrix **/
	inline FMatrix ApplyScale(float Scale) const;

	// @return the origin of the co-ordinate system
	inline FVector GetOrigin() const;

	/**
	 * get axes of this matrix scaled by the scale of the matrix
	 *
	 * @param X axes returned to this param
	 * @param Y axes returned to this param
	 * @param Z axes returned to this param
	 */
	inline void GetScaledAxes(FVector& X, FVector& Y, FVector& Z) const;

	/**
	 * get unit length axes of this matrix
	 *
	 * @param X axes returned to this param
	 * @param Y axes returned to this param
	 * @param Z axes returned to this param
	 */
	inline void GetUnitAxes(FVector& X, FVector& Y, FVector& Z) const;

	/**
	 * set an axis of this matrix
	 *
	 * @param i index into the axis of the matrix
	 * @param Axis vector of the axis
	 */
	inline void SetAxis(int i, const FVector& Axis);

	// Set the origin of the coordinate system to the given vector
	inline void SetOrigin(const FVector& NewOrigin);

	/**
	 * Update the axes of the matrix if any value is NULL do not update that axis
	 *
	 * @param Axis0 set matrix row 0
	 * @param Axis1 set matrix row 1
	 * @param Axis2 set matrix row 2
	 * @param Origin set matrix row 3
	 */
	inline void SetAxes(FVector* Axis0 = NULL, FVector* Axis1 = NULL, FVector* Axis2 = NULL, FVector* Origin = NULL);


	/**
	 * get a column of this matrix
	 *
	 * @param i index into the column of the matrix
	 * @return vector of the column
	 */
	inline FVector GetColumn(int i) const;

	/**
	 * Set a column of this matrix
	 *
	 * @param i index of the matrix column
	 * @param Value new value of the column
	 */
	inline void SetColumn(int i, FVector Value);

	// Frustum plane extraction.
	/** @param OutPlane the near plane of the Frustum of this matrix */
	inline bool GetFrustumNearPlane(FPlane& OutPlane) const;

	/** @param OutPlane the far plane of the Frustum of this matrix */
	inline bool GetFrustumFarPlane(FPlane& OutPlane) const;

	/** @param OutPlane the left plane of the Frustum of this matrix */
	inline bool GetFrustumLeftPlane(FPlane& OutPlane) const;

	/** @param OutPlane the right plane of the Frustum of this matrix */
	inline bool GetFrustumRightPlane(FPlane& OutPlane) const;

	/** @param OutPlane the top plane of the Frustum of this matrix */
	inline bool GetFrustumTopPlane(FPlane& OutPlane) const;

	/** @param OutPlane the bottom plane of the Frustum of this matrix */
	inline bool GetFrustumBottomPlane(FPlane& OutPlane) const;

	/**
	 * Returns a vector based on 4 FLOATs.
	 *
	 * @param X		1st float component
	 * @param Y		2nd float component
	 * @param Z		3rd float component
	 * @param W		4th float component
	 * @return		Vector of the 4 FLOATs
	 */
	static inline VectorRegister MakeVectorRegister(float X, float Y, float Z, float W)
	{
		VectorRegister Vec = { { X, Y, Z, W } };
		return Vec;
	}

	/**
	 * Calculate Homogeneous transform.
	 *
	 * @param VecP			VectorRegister
	 * @param MatrixM		FMatrix pointer to the Matrix to apply transform
	 * @return VectorRegister = VecP*MatrixM
	 */
	static inline VectorRegister VectorTransformVector(const VectorRegister& VecP, const void* MatrixM)
	{
		typedef float Float4x4[4][4];
		union { VectorRegister v; float f[4]; } Tmp, Result;
		Tmp.v = VecP;
		const Float4x4& M = *((const Float4x4*)MatrixM);

		Result.f[0] = Tmp.f[0] * M[0][0] + Tmp.f[1] * M[1][0] + Tmp.f[2] * M[2][0] + Tmp.f[3] * M[3][0];
		Result.f[1] = Tmp.f[0] * M[0][1] + Tmp.f[1] * M[1][1] + Tmp.f[2] * M[2][1] + Tmp.f[3] * M[3][1];
		Result.f[2] = Tmp.f[0] * M[0][2] + Tmp.f[1] * M[1][2] + Tmp.f[2] * M[2][2] + Tmp.f[3] * M[3][2];
		Result.f[3] = Tmp.f[0] * M[0][3] + Tmp.f[1] * M[1][3] + Tmp.f[2] * M[2][3] + Tmp.f[3] * M[3][3];

		return Result.v;
	}

	/**
	 * Convert this Atom to the 3x4 transpose of the transformation matrix.
	 */
	inline void To3x4MatrixTranspose(float* Out) const
	{
		const float* Src = &(M[0][0]);
		float* Dest = Out;

		Dest[0] = Src[0];   // [0][0]
		Dest[1] = Src[4];   // [1][0]
		Dest[2] = Src[8];   // [2][0]
		Dest[3] = Src[12];  // [3][0]

		Dest[4] = Src[1];   // [0][1]
		Dest[5] = Src[5];   // [1][1]
		Dest[6] = Src[9];   // [2][1]
		Dest[7] = Src[13];  // [3][1]

		Dest[8] = Src[2];   // [0][2]
		Dest[9] = Src[6];   // [1][2]
		Dest[10] = Src[10]; // [2][2]
		Dest[11] = Src[14]; // [3][2]
	}

	static inline void VectorMatrixMultiply(void* Result, const void* Matrix1, const void* Matrix2)
	{
		typedef float Float4x4[4][4];
		const Float4x4& A = *((const Float4x4*)Matrix1);
		const Float4x4& B = *((const Float4x4*)Matrix2);
		Float4x4 Temp;
		Temp[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0] + A[0][3] * B[3][0];
		Temp[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1] + A[0][2] * B[2][1] + A[0][3] * B[3][1];
		Temp[0][2] = A[0][0] * B[0][2] + A[0][1] * B[1][2] + A[0][2] * B[2][2] + A[0][3] * B[3][2];
		Temp[0][3] = A[0][0] * B[0][3] + A[0][1] * B[1][3] + A[0][2] * B[2][3] + A[0][3] * B[3][3];

		Temp[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0] + A[1][2] * B[2][0] + A[1][3] * B[3][0];
		Temp[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1] + A[1][2] * B[2][1] + A[1][3] * B[3][1];
		Temp[1][2] = A[1][0] * B[0][2] + A[1][1] * B[1][2] + A[1][2] * B[2][2] + A[1][3] * B[3][2];
		Temp[1][3] = A[1][0] * B[0][3] + A[1][1] * B[1][3] + A[1][2] * B[2][3] + A[1][3] * B[3][3];

		Temp[2][0] = A[2][0] * B[0][0] + A[2][1] * B[1][0] + A[2][2] * B[2][0] + A[2][3] * B[3][0];
		Temp[2][1] = A[2][0] * B[0][1] + A[2][1] * B[1][1] + A[2][2] * B[2][1] + A[2][3] * B[3][1];
		Temp[2][2] = A[2][0] * B[0][2] + A[2][1] * B[1][2] + A[2][2] * B[2][2] + A[2][3] * B[3][2];
		Temp[2][3] = A[2][0] * B[0][3] + A[2][1] * B[1][3] + A[2][2] * B[2][3] + A[2][3] * B[3][3];

		Temp[3][0] = A[3][0] * B[0][0] + A[3][1] * B[1][0] + A[3][2] * B[2][0] + A[3][3] * B[3][0];
		Temp[3][1] = A[3][0] * B[0][1] + A[3][1] * B[1][1] + A[3][2] * B[2][1] + A[3][3] * B[3][1];
		Temp[3][2] = A[3][0] * B[0][2] + A[3][1] * B[1][2] + A[3][2] * B[2][2] + A[3][3] * B[3][2];
		Temp[3][3] = A[3][0] * B[0][3] + A[3][1] * B[1][3] + A[3][2] * B[2][3] + A[3][3] * B[3][3];
		memcpy(Result, &Temp, 16 * sizeof(float));
	}

	/**
	 * Calculate the inverse of an FMatrix.
	 *
	 * @param DstMatrix		FMatrix pointer to where the result should be stored
	 * @param SrcMatrix		FMatrix pointer to the Matrix to be inversed
	 */
	static inline void VectorMatrixInverse(void* DstMatrix, const void* SrcMatrix)
	{
		typedef float Float4x4[4][4];
		const Float4x4& M = *((const Float4x4*)SrcMatrix);
		Float4x4 Result;
		float Det[4];
		Float4x4 Tmp;

		Tmp[0][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
		Tmp[0][1] = M[1][2] * M[3][3] - M[1][3] * M[3][2];
		Tmp[0][2] = M[1][2] * M[2][3] - M[1][3] * M[2][2];

		Tmp[1][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
		Tmp[1][1] = M[0][2] * M[3][3] - M[0][3] * M[3][2];
		Tmp[1][2] = M[0][2] * M[2][3] - M[0][3] * M[2][2];

		Tmp[2][0] = M[1][2] * M[3][3] - M[1][3] * M[3][2];
		Tmp[2][1] = M[0][2] * M[3][3] - M[0][3] * M[3][2];
		Tmp[2][2] = M[0][2] * M[1][3] - M[0][3] * M[1][2];

		Tmp[3][0] = M[1][2] * M[2][3] - M[1][3] * M[2][2];
		Tmp[3][1] = M[0][2] * M[2][3] - M[0][3] * M[2][2];
		Tmp[3][2] = M[0][2] * M[1][3] - M[0][3] * M[1][2];

		Det[0] = M[1][1] * Tmp[0][0] - M[2][1] * Tmp[0][1] + M[3][1] * Tmp[0][2];
		Det[1] = M[0][1] * Tmp[1][0] - M[2][1] * Tmp[1][1] + M[3][1] * Tmp[1][2];
		Det[2] = M[0][1] * Tmp[2][0] - M[1][1] * Tmp[2][1] + M[3][1] * Tmp[2][2];
		Det[3] = M[0][1] * Tmp[3][0] - M[1][1] * Tmp[3][1] + M[2][1] * Tmp[3][2];

		float Determinant = M[0][0] * Det[0] - M[1][0] * Det[1] + M[2][0] * Det[2] - M[3][0] * Det[3];
		const float	RDet = 1.0f / Determinant;

		Result[0][0] = RDet * Det[0];
		Result[0][1] = -RDet * Det[1];
		Result[0][2] = RDet * Det[2];
		Result[0][3] = -RDet * Det[3];
		Result[1][0] = -RDet * (M[1][0] * Tmp[0][0] - M[2][0] * Tmp[0][1] + M[3][0] * Tmp[0][2]);
		Result[1][1] = RDet * (M[0][0] * Tmp[1][0] - M[2][0] * Tmp[1][1] + M[3][0] * Tmp[1][2]);
		Result[1][2] = -RDet * (M[0][0] * Tmp[2][0] - M[1][0] * Tmp[2][1] + M[3][0] * Tmp[2][2]);
		Result[1][3] = RDet * (M[0][0] * Tmp[3][0] - M[1][0] * Tmp[3][1] + M[2][0] * Tmp[3][2]);
		Result[2][0] = RDet * (
			M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
			M[2][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) +
			M[3][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1])
			);
		Result[2][1] = -RDet * (
			M[0][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
			M[2][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
			M[3][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1])
			);
		Result[2][2] = RDet * (
			M[0][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) -
			M[1][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
			M[3][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
			);
		Result[2][3] = -RDet * (
			M[0][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]) -
			M[1][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1]) +
			M[2][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
			);
		Result[3][0] = -RDet * (
			M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
			M[2][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) +
			M[3][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])
			);
		Result[3][1] = RDet * (
			M[0][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
			M[2][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
			M[3][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1])
			);
		Result[3][2] = -RDet * (
			M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) -
			M[1][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
			M[3][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
			);
		Result[3][3] = RDet * (
			M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
			M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
			M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
			);

		memcpy(DstMatrix, &Result, 16 * sizeof(float));
	}
};

inline FMatrix::FMatrix()
{
	memset(this, 0, sizeof(float) * 4 * 4);
}

inline FMatrix::FMatrix(const FPlane& InX, const FPlane& InY, const FPlane& InZ, const FPlane& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = InX.W;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = InY.W;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = InZ.W;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = InW.W;
}

inline FMatrix::FMatrix(const FVector& InX, const FVector& InY, const FVector& InZ, const FVector& InW)
{
	M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = 0.0f;
	M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = 0.0f;
	M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = 0.0f;
	M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = 1.0f;
}


inline void FMatrix::SetIdentity()
{
	M[0][0] = 1; M[0][1] = 0;  M[0][2] = 0;  M[0][3] = 0;
	M[1][0] = 0; M[1][1] = 1;  M[1][2] = 0;  M[1][3] = 0;
	M[2][0] = 0; M[2][1] = 0;  M[2][2] = 1;  M[2][3] = 0;
	M[3][0] = 0; M[3][1] = 0;  M[3][2] = 0;  M[3][3] = 1;
}

inline void FMatrix::operator*=(const FMatrix& Other)
{
	VectorMatrixMultiply(this, this, &Other);
}


inline FMatrix FMatrix::operator*(const FMatrix& Other) const
{
	FMatrix Result;
	VectorMatrixMultiply(&Result, this, &Other);
	return Result;
}


inline FMatrix	FMatrix::operator+(const FMatrix& Other) const
{
	FMatrix ResultMat;

	for (int X = 0; X < 4; X++)
	{
		for (int Y = 0; Y < 4; Y++)
		{
			ResultMat.M[X][Y] = M[X][Y] + Other.M[X][Y];
		}
	}

	return ResultMat;
}

inline void FMatrix::operator+=(const FMatrix& Other)
{
	*this = *this + Other;
}

inline FMatrix	FMatrix::operator*(float Other) const
{
	FMatrix ResultMat;

	for (int X = 0; X < 4; X++)
	{
		for (int Y = 0; Y < 4; Y++)
		{
			ResultMat.M[X][Y] = M[X][Y] * Other;
		}
	}

	return ResultMat;
}

inline void FMatrix::operator*=(float Other)
{
	*this = *this * Other;
}

// Comparison operators.

inline bool FMatrix::operator==(const FMatrix& Other) const
{
	for (int X = 0; X < 4; X++)
	{
		for (int Y = 0; Y < 4; Y++)
		{
			if (M[X][Y] != Other.M[X][Y])
			{
				return false;
			}
		}
	}

	return true;
}

// Error-tolerant comparison.
inline bool FMatrix::Equals(const FMatrix& Other, float Tolerance/*=KINDA_SMALL_NUMBER*/) const
{
	for (int X = 0; X < 4; X++)
	{
		for (int Y = 0; Y < 4; Y++)
		{
			if (std::abs(M[X][Y] - Other.M[X][Y]) > Tolerance)
			{
				return false;
			}
		}
	}

	return true;
}

inline bool FMatrix::operator!=(const FMatrix& Other) const
{
	return !(*this == Other);
}


// Homogeneous transform.

inline FVector4 FMatrix::TransformFVector4(const FVector4& P) const
{
	FVector4 Result;
	VectorRegister VecP = MakeVectorRegister(((const float*)(&P))[0], ((const float*)(&P))[1], ((const float*)(&P))[2], ((const float*)(&P))[3]);
	VectorRegister VecR = VectorTransformVector(VecP, this);
	memcpy(&Result, &VecR, sizeof(VectorRegister));
	return Result;
}


// Transform position

/** Transform a location - will take into account translation part of the FMatrix. */
inline FVector4 FMatrix::TransformPosition(const FVector& V) const
{
	return TransformFVector4(FVector4(V.X, V.Y, V.Z, 1.0f));
}

/** Inverts the matrix and then transforms V - correctly handles scaling in this matrix. */
inline FVector FMatrix::InverseTransformPosition(const FVector& V) const
{
	FMatrix InvSelf = this->InverseFast();
	return InvSelf.TransformPosition(V);
}

// Transform vector

/**
 *	Transform a direction vector - will not take into account translation part of the FMatrix.
 *	If you want to transform a surface normal (or plane) and correctly account for non-uniform scaling you should use TransformByUsingAdjointT.
 */
inline FVector4 FMatrix::TransformVector(const FVector& V) const
{
	return TransformFVector4(FVector4(V.X, V.Y, V.Z, 0.0f));
}

/** Faster version of InverseTransformVector that assumes no scaling. WARNING: Will NOT work correctly if there is scaling in the matrix. */
inline FVector FMatrix::InverseTransformVector(const FVector& V) const
{
	FMatrix InvSelf = this->InverseFast();
	return InvSelf.TransformVector(V);
}


// Transpose.

inline FMatrix FMatrix::GetTransposed() const
{
	FMatrix	Result;

	Result.M[0][0] = M[0][0];
	Result.M[0][1] = M[1][0];
	Result.M[0][2] = M[2][0];
	Result.M[0][3] = M[3][0];

	Result.M[1][0] = M[0][1];
	Result.M[1][1] = M[1][1];
	Result.M[1][2] = M[2][1];
	Result.M[1][3] = M[3][1];

	Result.M[2][0] = M[0][2];
	Result.M[2][1] = M[1][2];
	Result.M[2][2] = M[2][2];
	Result.M[2][3] = M[3][2];

	Result.M[3][0] = M[0][3];
	Result.M[3][1] = M[1][3];
	Result.M[3][2] = M[2][3];
	Result.M[3][3] = M[3][3];

	return Result;
}

// Determinant.

inline float FMatrix::Determinant() const
{
	return	M[0][0] * (
		M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
		M[2][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
		M[3][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
		) -
		M[1][0] * (
			M[0][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
			M[2][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
			M[3][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
			) +
		M[2][0] * (
			M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) -
			M[1][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
			M[3][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
			) -
		M[3][0] * (
			M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) -
			M[1][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2]) +
			M[2][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
			);
}

/** Calculate determinant of rotation 3x3 matrix */
inline float FMatrix::RotDeterminant() const
{
	return
		M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
		M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
		M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]);
}

// Inverse.
/** Fast path, doesn't check for nil matrices in final release builds */
inline FMatrix FMatrix::InverseFast() const
{
	FMatrix Result;
	VectorMatrixInverse(&Result, this);
	return Result;
}

inline FMatrix FMatrix::TransposeAdjoint() const
{
	FMatrix TA;

	TA.M[0][0] = this->M[1][1] * this->M[2][2] - this->M[1][2] * this->M[2][1];
	TA.M[0][1] = this->M[1][2] * this->M[2][0] - this->M[1][0] * this->M[2][2];
	TA.M[0][2] = this->M[1][0] * this->M[2][1] - this->M[1][1] * this->M[2][0];
	TA.M[0][3] = 0.f;

	TA.M[1][0] = this->M[2][1] * this->M[0][2] - this->M[2][2] * this->M[0][1];
	TA.M[1][1] = this->M[2][2] * this->M[0][0] - this->M[2][0] * this->M[0][2];
	TA.M[1][2] = this->M[2][0] * this->M[0][1] - this->M[2][1] * this->M[0][0];
	TA.M[1][3] = 0.f;

	TA.M[2][0] = this->M[0][1] * this->M[1][2] - this->M[0][2] * this->M[1][1];
	TA.M[2][1] = this->M[0][2] * this->M[1][0] - this->M[0][0] * this->M[1][2];
	TA.M[2][2] = this->M[0][0] * this->M[1][1] - this->M[0][1] * this->M[1][0];
	TA.M[2][3] = 0.f;

	TA.M[3][0] = 0.f;
	TA.M[3][1] = 0.f;
	TA.M[3][2] = 0.f;
	TA.M[3][3] = 1.f;

	return TA;
}

// NOTE: There is some compiler optimization issues with WIN64 that cause inline to cause a crash
// Remove any scaling from this matrix (ie magnitude of each row is 1)
inline void FMatrix::RemoveScaling(float Tolerance/*=SMALL_NUMBER*/)
{
	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	const float SquareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
	const float SquareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
	const float SquareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);
	const float Scale0 = FMath::FloatSelect(SquareSum0 - Tolerance, FMath::InvSqrt(SquareSum0), 1.0f);
	const float Scale1 = FMath::FloatSelect(SquareSum1 - Tolerance, FMath::InvSqrt(SquareSum1), 1.0f);
	const float Scale2 = FMath::FloatSelect(SquareSum2 - Tolerance, FMath::InvSqrt(SquareSum2), 1.0f);
	M[0][0] *= Scale0;
	M[0][1] *= Scale0;
	M[0][2] *= Scale0;
	M[1][0] *= Scale1;
	M[1][1] *= Scale1;
	M[1][2] *= Scale1;
	M[2][0] *= Scale2;
	M[2][1] *= Scale2;
	M[2][2] *= Scale2;
}

// Returns matrix without scale information
inline FMatrix FMatrix::GetMatrixWithoutScale(float Tolerance/*=SMALL_NUMBER*/) const
{
	FMatrix Result = *this;
	Result.RemoveScaling(Tolerance);
	return Result;
}

/** Remove any scaling from this matrix (ie magnitude of each row is 1) and return the 3D scale vector that was initially present. */
inline FVector FMatrix::ExtractScaling(float Tolerance/*=SMALL_NUMBER*/)
{
	FVector Scale3D(0, 0, 0);

	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	const float SquareSum0 = (M[0][0] * M[0][0]) + (M[0][1] * M[0][1]) + (M[0][2] * M[0][2]);
	const float SquareSum1 = (M[1][0] * M[1][0]) + (M[1][1] * M[1][1]) + (M[1][2] * M[1][2]);
	const float SquareSum2 = (M[2][0] * M[2][0]) + (M[2][1] * M[2][1]) + (M[2][2] * M[2][2]);

	if (SquareSum0 > Tolerance)
	{
		float Scale0 = std::sqrt(SquareSum0);
		Scale3D[0] = Scale0;
		float InvScale0 = 1.f / Scale0;
		M[0][0] *= InvScale0;
		M[0][1] *= InvScale0;
		M[0][2] *= InvScale0;
	}
	else
	{
		Scale3D[0] = 0;
	}

	if (SquareSum1 > Tolerance)
	{
		float Scale1 = std::sqrt(SquareSum1);
		Scale3D[1] = Scale1;
		float InvScale1 = 1.f / Scale1;
		M[1][0] *= InvScale1;
		M[1][1] *= InvScale1;
		M[1][2] *= InvScale1;
	}
	else
	{
		Scale3D[1] = 0;
	}

	if (SquareSum2 > Tolerance)
	{
		float Scale2 = std::sqrt(SquareSum2);
		Scale3D[2] = Scale2;
		float InvScale2 = 1.f / Scale2;
		M[2][0] *= InvScale2;
		M[2][1] *= InvScale2;
		M[2][2] *= InvScale2;
	}
	else
	{
		Scale3D[2] = 0;
	}

	return Scale3D;
}

/** return a 3D scale vector calculated from this matrix (where each component is the magnitude of a row vector). */
inline FVector FMatrix::GetScaleVector(float Tolerance/*=SMALL_NUMBER*/) const
{
	FVector Scale3D(1, 1, 1);

	// For each row, find magnitude, and if its non-zero re-scale so its unit length.
	for (int i = 0; i < 3; i++)
	{
		const float SquareSum = (M[i][0] * M[i][0]) + (M[i][1] * M[i][1]) + (M[i][2] * M[i][2]);
		if (SquareSum > Tolerance)
		{
			Scale3D[i] = std::sqrt(SquareSum);
		}
		else
		{
			Scale3D[i] = 0.f;
		}
	}

	return Scale3D;
}
// Remove any translation from this matrix
inline FMatrix FMatrix::RemoveTranslation() const
{
	FMatrix Result = *this;
	Result.M[3][0] = 0.0f;
	Result.M[3][1] = 0.0f;
	Result.M[3][2] = 0.0f;
	return Result;
}

inline FMatrix FMatrix::ConcatTranslation(const FVector& Translation) const
{
	FMatrix Result;

	float* Dest = &Result.M[0][0];
	const float* Src = &M[0][0];
	const float* Trans = &Translation.X;

	Dest[0] = Src[0];
	Dest[1] = Src[1];
	Dest[2] = Src[2];
	Dest[3] = Src[3];
	Dest[4] = Src[4];
	Dest[5] = Src[5];
	Dest[6] = Src[6];
	Dest[7] = Src[7];
	Dest[8] = Src[8];
	Dest[9] = Src[9];
	Dest[10] = Src[10];
	Dest[11] = Src[11];
	Dest[12] = Src[12] + Trans[0];
	Dest[13] = Src[13] + Trans[1];
	Dest[14] = Src[14] + Trans[2];
	Dest[15] = Src[15];

	return Result;
}

inline void FMatrix::ScaleTranslation(const FVector& InScale3D)
{
	M[3][0] *= InScale3D.X;
	M[3][1] *= InScale3D.Y;
	M[3][2] *= InScale3D.Z;
}

// GetOrigin

inline FVector FMatrix::GetOrigin() const
{
	return FVector(M[3][0], M[3][1], M[3][2]);
}

inline void FMatrix::GetScaledAxes(FVector& X, FVector& Y, FVector& Z) const
{
	X.X = M[0][0]; X.Y = M[0][1]; X.Z = M[0][2];
	Y.X = M[1][0]; Y.Y = M[1][1]; Y.Z = M[1][2];
	Z.X = M[2][0]; Z.Y = M[2][1]; Z.Z = M[2][2];
}

inline void FMatrix::GetUnitAxes(FVector& X, FVector& Y, FVector& Z) const
{
	GetScaledAxes(X, Y, Z);
	X.Normalize();
	Y.Normalize();
	Z.Normalize();
}

inline void FMatrix::SetAxis(int i, const FVector& Axis)
{
	M[i][0] = Axis.X;
	M[i][1] = Axis.Y;
	M[i][2] = Axis.Z;
}

inline void FMatrix::SetOrigin(const FVector& NewOrigin)
{
	M[3][0] = NewOrigin.X;
	M[3][1] = NewOrigin.Y;
	M[3][2] = NewOrigin.Z;
}

inline void FMatrix::SetAxes(FVector* Axis0 /*= NULL*/, FVector* Axis1 /*= NULL*/, FVector* Axis2 /*= NULL*/, FVector* Origin /*= NULL*/)
{
	if (Axis0 != NULL)
	{
		M[0][0] = Axis0->X;
		M[0][1] = Axis0->Y;
		M[0][2] = Axis0->Z;
	}
	if (Axis1 != NULL)
	{
		M[1][0] = Axis1->X;
		M[1][1] = Axis1->Y;
		M[1][2] = Axis1->Z;
	}
	if (Axis2 != NULL)
	{
		M[2][0] = Axis2->X;
		M[2][1] = Axis2->Y;
		M[2][2] = Axis2->Z;
	}
	if (Origin != NULL)
	{
		M[3][0] = Origin->X;
		M[3][1] = Origin->Y;
		M[3][2] = Origin->Z;
	}
}

inline FVector FMatrix::GetColumn(int i) const
{
	return FVector(M[0][i], M[1][i], M[2][i]);
}

inline void FMatrix::SetColumn(int i, FVector Value)
{
	M[0][i] = Value.X;
	M[1][i] = Value.Y;
	M[2][i] = Value.Z;
}

inline bool MakeFrustumPlane(float A, float B, float C, float D, FPlane& OutPlane)
{
	const float	LengthSquared = A * A + B * B + C * C;
	if (LengthSquared > DELTA * DELTA)
	{
		const float	InvLength = FMath::InvSqrt(LengthSquared);
		OutPlane = FPlane(-A * InvLength, -B * InvLength, -C * InvLength, D * InvLength);
		return 1;
	}
	else
		return 0;
}

// Frustum plane extraction.
inline bool FMatrix::GetFrustumNearPlane(FPlane& OutPlane) const
{
	return MakeFrustumPlane(
		M[0][2],
		M[1][2],
		M[2][2],
		M[3][2],
		OutPlane
	);
}

inline bool FMatrix::GetFrustumFarPlane(FPlane& OutPlane) const
{
	return MakeFrustumPlane(
		M[0][3] - M[0][2],
		M[1][3] - M[1][2],
		M[2][3] - M[2][2],
		M[3][3] - M[3][2],
		OutPlane
	);
}

inline bool FMatrix::GetFrustumLeftPlane(FPlane& OutPlane) const
{
	return MakeFrustumPlane(
		M[0][3] + M[0][0],
		M[1][3] + M[1][0],
		M[2][3] + M[2][0],
		M[3][3] + M[3][0],
		OutPlane
	);
}

inline bool FMatrix::GetFrustumRightPlane(FPlane& OutPlane) const
{
	return MakeFrustumPlane(
		M[0][3] - M[0][0],
		M[1][3] - M[1][0],
		M[2][3] - M[2][0],
		M[3][3] - M[3][0],
		OutPlane
	);
}

inline bool FMatrix::GetFrustumTopPlane(FPlane& OutPlane) const
{
	return MakeFrustumPlane(
		M[0][3] - M[0][1],
		M[1][3] - M[1][1],
		M[2][3] - M[2][1],
		M[3][3] - M[3][1],
		OutPlane
	);
}

inline bool FMatrix::GetFrustumBottomPlane(FPlane& OutPlane) const
{
	return MakeFrustumPlane(
		M[0][3] + M[0][1],
		M[1][3] + M[1][1],
		M[2][3] + M[2][1],
		M[3][3] + M[3][1],
		OutPlane
	);
}

/**
 * Apply Scale to this matrix
 */
inline FMatrix FMatrix::ApplyScale(float Scale) const
{
	FMatrix ScaleMatrix(
		FPlane(Scale, 0.0f, 0.0f, 0.0f),
		FPlane(0.0f, Scale, 0.0f, 0.0f),
		FPlane(0.0f, 0.0f, Scale, 0.0f),
		FPlane(0.0f, 0.0f, 0.0f, 1.0f)
	);
	return ScaleMatrix * (*this);
}


class FTranslationMatrix : public FMatrix
{
public:

	/** Constructor translation matrix based on given vector */
	FTranslationMatrix(const FVector& Delta);

	/** Matrix factory. Return an FMatrix so we don't have type conversion issues in expressions. */
	static FMatrix Make(FVector const& Delta)
	{
		return FTranslationMatrix(Delta);
	}
};


inline FTranslationMatrix::FTranslationMatrix(const FVector& Delta)
	: FMatrix(
		FPlane(1.0f, 0.0f, 0.0f, 0.0f),
		FPlane(0.0f, 1.0f, 0.0f, 0.0f),
		FPlane(0.0f, 0.0f, 1.0f, 0.0f),
		FPlane(Delta.X, Delta.Y, Delta.Z, 1.0f)
	)
{

}


class FReversedZPerspectiveMatrix : public FMatrix
{
public:
	FReversedZPerspectiveMatrix(float HalfFOVX, float HalfFOVY, float MultFOVX, float MultFOVY, float MinZ, float MaxZ);
	FReversedZPerspectiveMatrix(float HalfFOV, float Width, float Height, float MinZ, float MaxZ);
	FReversedZPerspectiveMatrix(float HalfFOV, float Width, float Height, float MinZ);
};

inline FReversedZPerspectiveMatrix::FReversedZPerspectiveMatrix(float HalfFOVX, float HalfFOVY, float MultFOVX, float MultFOVY, float MinZ, float MaxZ)
	: FMatrix(
		FPlane(MultFOVX / std::tan(HalfFOVX), 0.0f, 0.0f, 0.0f),
		FPlane(0.0f, MultFOVY / std::tan(HalfFOVY), 0.0f, 0.0f),
		FPlane(0.0f, 0.0f, ((MinZ == MaxZ) ? 0.0f : MinZ / (MinZ - MaxZ)), 1.0f),
		FPlane(0.0f, 0.0f, ((MinZ == MaxZ) ? MinZ : -MaxZ * MinZ / (MinZ - MaxZ)), 0.0f)
	)
{
}


inline FReversedZPerspectiveMatrix::FReversedZPerspectiveMatrix(float HalfFOV, float Width, float Height, float MinZ, float MaxZ)
	: FMatrix(
		FPlane(1.0f / std::tan(HalfFOV), 0.0f, 0.0f, 0.0f),
		FPlane(0.0f, Width / std::tan(HalfFOV) / Height, 0.0f, 0.0f),
		FPlane(0.0f, 0.0f, ((MinZ == MaxZ) ? 0.0f : MinZ / (MinZ - MaxZ)), 1.0f),
		FPlane(0.0f, 0.0f, ((MinZ == MaxZ) ? MinZ : -MaxZ * MinZ / (MinZ - MaxZ)), 0.0f)
	)
{
}


inline FReversedZPerspectiveMatrix::FReversedZPerspectiveMatrix(float HalfFOV, float Width, float Height, float MinZ)
	: FMatrix(
		FPlane(1.0f / std::tan(HalfFOV), 0.0f, 0.0f, 0.0f),
		FPlane(0.0f, Width / std::tan(HalfFOV) / Height, 0.0f, 0.0f),
		FPlane(0.0f, 0.0f, 0.0f, 1.0f),
		FPlane(0.0f, 0.0f, MinZ, 0.0f)
	)
{
}


/** Inverse Rotation matrix */
class FInverseRotationMatrix
	: public FMatrix
{
public:
	/**
	 * Constructor.
	 *
	 * @param Rot rotation
	 */
	FInverseRotationMatrix(const FRotator& Rot);
};


inline FInverseRotationMatrix::FInverseRotationMatrix(const FRotator& Rot)
	: FMatrix(
		FMatrix( // Yaw
			FPlane(+std::cos(Rot.Yaw * PI / 180.f), -std::sin(Rot.Yaw * PI / 180.f), 0.0f, 0.0f),
			FPlane(+std::sin(Rot.Yaw * PI / 180.f), +std::cos(Rot.Yaw * PI / 180.f), 0.0f, 0.0f),
			FPlane(0.0f, 0.0f, 1.0f, 0.0f),
			FPlane(0.0f, 0.0f, 0.0f, 1.0f))*
		FMatrix( // Pitch
			FPlane(+std::cos(Rot.Pitch * PI / 180.f), 0.0f, -std::sin(Rot.Pitch * PI / 180.f), 0.0f),
			FPlane(0.0f, 1.0f, 0.0f, 0.0f),
			FPlane(+std::sin(Rot.Pitch * PI / 180.f), 0.0f, +std::cos(Rot.Pitch * PI / 180.f), 0.0f),
			FPlane(0.0f, 0.0f, 0.0f, 1.0f))*
		FMatrix( // Roll
			FPlane(1.0f, 0.0f, 0.0f, 0.0f),
			FPlane(0.0f, +std::cos(Rot.Roll * PI / 180.f), +std::sin(Rot.Roll * PI / 180.f), 0.0f),
			FPlane(0.0f, -std::sin(Rot.Roll * PI / 180.f), +std::cos(Rot.Roll * PI / 180.f), 0.0f),
			FPlane(0.0f, 0.0f, 0.0f, 1.0f))
	)
{
}

