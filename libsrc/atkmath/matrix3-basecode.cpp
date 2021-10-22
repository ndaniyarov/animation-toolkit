#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

Vector3 Matrix3::toEulerAnglesXYZ() const
{
   float x,y,z;
   if (m13 == 1 || m13 == -1){
      if (m13 == 1) {
         y = M_PI/2.0f;
         x = atan2(m21,m22);
      }
      if (m13 == -1) {
         y = -M_PI/2.0f;
         x = atan2(-m21,m22);
      }
      z = 0.0f;
   }
   else { 
      y = asin(m13);
      z = atan2(-m12, m11);
      x = atan2(-m23, m33);
   }
   Vector3 euler = Vector3(x,y,z);
   return euler;
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
   float x,y,z;
   if (m12 == 1 || m12 == -1){
      if (m12 == 1) {
         z = -M_PI/2.0f;
         x = atan2(-m31,-m21);
      }
      if (m12 == -1) {
         z = M_PI/2.0f;
         x = atan2(m31,m21);
      }
      y = 0.0f;
   }
   else { 
      z = asin(-m12);
      y = atan2(m13, m11);
      x = atan2(m32, m22);
   }
   Vector3 euler = Vector3(x,y,z);
   return euler;
}

//this might be an issue with 90
Vector3 Matrix3::toEulerAnglesYXZ() const
{
   float x,y,z;
   if (m23 == 1 || m23 == -1){
      if (m23 == 1) {
         x = -M_PI/2.0f;
         y = atan2(-m12,m11);
      }
      if (m23 == -1) {
         x = M_PI/2.0f;
         y = atan2(m12,m32);
      }
      z = 0.0f;
   }
   else { 
      x = asin(-m23);
      z = atan2(m21, m22);
      y = atan2(m13, m33);
   }
   Vector3 euler = Vector3(x,y,z);
   return euler;
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
   float x,y,z;
   if (m21 == 1 || m21 == -1){
      if (m21 == 1) {
         z = M_PI/2.0f;
         x = atan2(m32,m33);
      }
      if (m21 == -1) {
         z = -M_PI/2.0f;
         x = atan2(m32,m33);
      }
      y = 0.0f;
   }
   else { 
      z = asin(m21);
      x = atan2(-m23, m22);
      y = atan2(-m31, m11);
   }
   Vector3 euler = Vector3(x,y,z);
   return euler;
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
   float x,y,z;
   if (m32 == 1 || m32 == -1){
      if (m32 == 1) {
         x = M_PI/2.0f;
         y = atan2(m21,m11);
      }
      if (m32 == -1) {
         x = -M_PI/2.0f;
         y = atan2(-m21,m11);
      }
      z = 0.0f;
   }
   else { 
      x = asin(m32);
      y = atan2(-m31, m33);
      z = atan2(-m12, m22);
   }
   Vector3 euler = Vector3(x,y,z);
   return euler;
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
   float x,y,z;
   if (m31 == 1 || m31 == -1){
      if (m31 == 1) {
         y = -M_PI/2.0f;
         x = atan2(-m12,-m13);
      }
      if (m31 == -1) {
         y = M_PI/2.0f;
         x = atan2(m12,m13);
      }
      z = 0.0f;
   }
   else { 
      y = asin(-1.0f * m31);
      z = atan2(m21, m11);
      x = atan2(m32, m33);
   }
   Vector3 euler = Vector3(x,y,z);
   return euler;
}

void Matrix3::fromEulerAnglesXYZ(const Vector3& angleRad)
{
   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];
   
   Matrix3 X,Y,Z,XYZ;
   
   X.m11 = 1.0f; X.m12 = 0.0f; X.m13 = 0.0f;
   X.m21 = 0.0f; X.m22 = cos(x); X.m23 = -sin(x);
   X.m31 = 0.0f; X.m32 = sin(x); X.m33 = cos(x);

   Y.m11 = cos(y); Y.m12 = 0.0f; Y.m13 = sin(y);
   Y.m21 = 0.0f; Y.m22 = 1.0f; Y.m23 = 0.0f;
   Y.m31 = -sin(y); Y.m32 = 0.0f; Y.m33 = cos(y);

   Z.m11 = cos(z); Z.m12 = -sin(z); Z.m13 = 0.0f;
   Z.m21 = sin(z); Z.m22 = cos(z); Z.m23 = 0.0f;
   Z.m31 = 0.0f; Z.m32 = 0.0f; Z.m33 = 1.0f;

   XYZ = X*Y*Z;

   *this = XYZ;
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{
   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];
   
   Matrix3 X,Y,Z,XZY;
   
   X.m11 = 1.0f; X.m12 = 0.0f; X.m13 = 0.0f;
   X.m21 = 0.0f; X.m22 = cos(x); X.m23 = -sin(x);
   X.m31 = 0.0f; X.m32 = sin(x); X.m33 = cos(x);

   Y.m11 = cos(y); Y.m12 = 0.0f; Y.m13 = sin(y);
   Y.m21 = 0.0f; Y.m22 = 1.0f; Y.m23 = 0.0f;
   Y.m31 = -sin(y); Y.m32 = 0.0f; Y.m33 = cos(y);

   Z.m11 = cos(z); Z.m12 = -sin(z); Z.m13 = 0.0f;
   Z.m21 = sin(z); Z.m22 = cos(z); Z.m23 = 0.0f;
   Z.m31 = 0.0f; Z.m32 = 0.0f; Z.m33 = 1.0f;

   XZY = X*Z*Y;



   *this = XZY;
}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{
   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];
   
   Matrix3 X,Y,Z,YXZ;
   
   X.m11 = 1.0f; X.m12 = 0.0f; X.m13 = 0.0f;
   X.m21 = 0.0f; X.m22 = cos(x); X.m23 = -sin(x);
   X.m31 = 0.0f; X.m32 = sin(x); X.m33 = cos(x);

   Y.m11 = cos(y); Y.m12 = 0.0f; Y.m13 = sin(y);
   Y.m21 = 0.0f; Y.m22 = 1.0f; Y.m23 = 0.0f;
   Y.m31 = -sin(y); Y.m32 = 0.0f; Y.m33 = cos(y);

   Z.m11 = cos(z); Z.m12 = -sin(z); Z.m13 = 0.0f;
   Z.m21 = sin(z); Z.m22 = cos(z); Z.m23 = 0.0f;
   Z.m31 = 0.0f; Z.m32 = 0.0f; Z.m33 = 1.0f;

   YXZ = Y*X*Z;



   *this = YXZ;
}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{
   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];
   
   Matrix3 X,Y,Z,YZX;
   
   X.m11 = 1.0f; X.m12 = 0.0f; X.m13 = 0.0f;
   X.m21 = 0.0f; X.m22 = cos(x); X.m23 = -sin(x);
   X.m31 = 0.0f; X.m32 = sin(x); X.m33 = cos(x);

   Y.m11 = cos(y); Y.m12 = 0.0f; Y.m13 = sin(y);
   Y.m21 = 0.0f; Y.m22 = 1.0f; Y.m23 = 0.0f;
   Y.m31 = -sin(y); Y.m32 = 0.0f; Y.m33 = cos(y);

   Z.m11 = cos(z); Z.m12 = -sin(z); Z.m13 = 0.0f;
   Z.m21 = sin(z); Z.m22 = cos(z); Z.m23 = 0.0f;
   Z.m31 = 0.0f; Z.m32 = 0.0f; Z.m33 = 1.0f;

   YZX = Y*Z*X;



   *this = YZX;
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];
   
   Matrix3 X,Y,Z,ZXY;
   
   X.m11 = 1.0f; X.m12 = 0.0f; X.m13 = 0.0f;
   X.m21 = 0.0f; X.m22 = cos(x); X.m23 = -sin(x);
   X.m31 = 0.0f; X.m32 = sin(x); X.m33 = cos(x);

   Y.m11 = cos(y); Y.m12 = 0.0f; Y.m13 = sin(y);
   Y.m21 = 0.0f; Y.m22 = 1.0f; Y.m23 = 0.0f;
   Y.m31 = -sin(y); Y.m32 = 0.0f; Y.m33 = cos(y);

   Z.m11 = cos(z); Z.m12 = -sin(z); Z.m13 = 0.0f;
   Z.m21 = sin(z); Z.m22 = cos(z); Z.m23 = 0.0f;
   Z.m31 = 0.0f; Z.m32 = 0.0f; Z.m33 = 1.0f;

   ZXY = Z*X*Y;



   *this = ZXY;
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
   float x = angleRad[0];
   float y = angleRad[1];
   float z = angleRad[2];
   
   Matrix3 X,Y,Z,ZYX;
   
   X.m11 = 1.0f; X.m12 = 0.0f; X.m13 = 0.0f;
   X.m21 = 0.0f; X.m22 = cos(x); X.m23 = -sin(x);
   X.m31 = 0.0f; X.m32 = sin(x); X.m33 = cos(x);

   Y.m11 = cos(y); Y.m12 = 0.0f; Y.m13 = sin(y);
   Y.m21 = 0.0f; Y.m22 = 1.0f; Y.m23 = 0.0f;
   Y.m31 = -sin(y); Y.m32 = 0.0f; Y.m33 = cos(y);

   Z.m11 = cos(z); Z.m12 = -sin(z); Z.m13 = 0.0f;
   Z.m21 = sin(z); Z.m22 = cos(z); Z.m23 = 0.0f;
   Z.m31 = 0.0f; Z.m32 = 0.0f; Z.m33 = 1.0f;

   ZYX = Z*Y*X;

   *this = ZYX;
}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{
   Quaternion final;
   final.fromMatrix(*this);
   final.toAxisAngle(axis,angleRad);
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
   Quaternion final;
   final.fromAxisAngle(axis, angleRad);
   *this = final.toMatrix();
}

}