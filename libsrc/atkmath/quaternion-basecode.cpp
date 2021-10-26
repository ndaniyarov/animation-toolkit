#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	return Quaternion(1,0,0,0);
}

void Quaternion::toAxisAngle (Vector3& axis, double& angleRad) const
{
	angleRad = acos(mW)*2.0f;
		float x = mX/sin(angleRad/2.0f);
		float y = mY/sin(angleRad/2.0f);
		float z = mZ/sin(angleRad/2.0f);
		axis = Vector3(x,y,z);
}

void Quaternion::fromAxisAngle (const Vector3& axis, double angleRad)
{
	mX = sin(angleRad/2.0f) * axis.x();
	mY = sin(angleRad/2.0f) * axis.y();
	mZ = sin(angleRad/2.0f) * axis.z();
	mW = cos(angleRad/2.0f);
	 Quaternion q = Quaternion(mX,mY,mZ,mW);
	 *this = q;
	normalize();
}

Matrix3 Quaternion::toMatrix () const
{
	double m11 = 1.0f - 2.0f*(mY*mY + mZ*mZ);
	double m12 = 2.0f*(mX*mY - mW*mZ);
	double m13 = 2.0f*(mX*mZ + mW*mY);
	double m21 = 2.0f*(mX*mY + mW*mZ);
	double m22 = 1.0f - 2.0f*(mX*mX + mZ*mZ);
	double m23 = 2.0f*(mY*mZ - mW*mX);
	double m31 = 2.0f*(mX*mZ - mW*mY);
	double m32 = 2.0f*(mY*mZ + mW*mX);
	double m33 = 1.0f - 2.0f*(mY*mY + mX*mX);

	Matrix3 matrix = Matrix3(m11,m12,m13,m21,m22,m23,m31,m32,m33);
	return matrix;
}

void Quaternion::fromMatrix(const Matrix3& rot)
{
	double mWsq = (1.0f/4.0f)*(rot[0][0]+rot[1][1]+rot[2][2]+1.0f);
	double mXsq = (1.0f/4.0f)*(rot[0][0]-rot[1][1]-rot[2][2]+1.0f);
	double mYsq = (1.0f/4.0f)*(-rot[0][0]+rot[1][1]-rot[2][2]+1.0);
	double mZsq = (1.0f/4.0f)*(-rot[0][0]-rot[1][1]+rot[2][2]+1.0);

	double max = std::max(mWsq, mXsq);
	max = std::max(max,mYsq);
	max = std::max(max,mZsq);

	if (max == mWsq) {
		mW = sqrt(mWsq);
		mZ = (1.0f/(4.0f * mW))*(rot[1][0] - rot[0][1]);
		mY = (1.0f/(4.0f * mW))*(rot[0][2] - rot[2][0]);
		mX = (1.0f/(4.0f * mW))*(rot[2][1] - rot[1][2]);
	}
	else if (max == mXsq) {
		mX = sqrt(mXsq);
		mY = (1.0f/(4.0f * mX))*(rot[0][1] + rot[1][0]);
		mZ = (1.0f/(4.0f * mX))*(rot[0][2] + rot[2][0]);
		mW = (1.0f/(4.0f * mX))*(rot[2][1] - rot[1][2]);
	}
	else if (max == mYsq) {
		mY = sqrt(mYsq);
		mX = (1.0f/(4.0f * mY))*(rot[0][1] + rot[1][0]);
		mZ = (1.0f/(4.0f * mY))*(rot[1][2] + rot[2][1]);
		mW = (1.0f/(4.0f * mY))*(rot[0][2] - rot[2][0]);
	}
	else {
		mZ = sqrt(mZsq);
		mX = (1.0f/(4.0f * mZ))*(rot[0][2] + rot[2][0]);
		mY = (1.0f/(4.0f * mZ))*(rot[1][2] + rot[2][1]);
		mW = (1.0f/(4.0f * mZ))*(rot[1][0] - rot[0][1]);
	}
	Quaternion q = Quaternion(mX,mY,mZ,mW);
	*this = q;
	normalize();
}

}