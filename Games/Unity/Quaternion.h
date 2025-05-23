/**
 *  ============================================================================
 *  MIT License
 *
 *  Copyright (c) 2016 Eric Phillips
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *  ============================================================================
 *
 *
 *  This file implements a series of math functions for manipulating a
 *  quaternion.
 *
 *  Created by Eric Phillips on October 21, 2016.
 */

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#define SMALL_float 0.0000000001
#define PI 3.14159265358979323846264338327950288419716939937510f
#define Deg2Rad (2.f * PI / 360.f)
#define Rad2Deg (1.f / Deg2Rad)


/**
 * Attempt to include a header file if the file exists.
 * If the file does not exist, create a dummy data structure for that type.
 * If it cannot be determined if it exists, just attempt to include it.
 */
#ifdef __has_include
#   if __has_include("Vector3.h")
#       include "Vector3.h"
#   elif !defined(GMATH_VECTOR3)
#define GMATH_VECTOR3
        struct Vector3
        {
            union
            {
                struct
                {
                    float x;
                    float y;
                    float z;
                };
                float data[3];
            };

            inline Vector3() : x(0), y(0), z(0) {}
            inline Vector3(float data[]) : x(data[0]), y(data[1]), z(data[2])
                {}
            inline Vector3(float value) : x(value), y(value), z(value) {}
            inline Vector3(float x, float y) : x(x), y(y), z(0) {}
            inline Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

            static inline Vector3 Cross(Vector3 lhs, Vector3 rhs)
            {
                float x = lhs.y * rhs.z - lhs.z * rhs.y;
                float y = lhs.z * rhs.x - lhs.x * rhs.z;
                float z = lhs.x * rhs.y - lhs.y * rhs.x;
                return Vector3(x, y, z);
            }

            static inline float Dot(Vector3 lhs, Vector3 rhs)
            {
                return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
            }

            static inline Vector3 Normalized(Vector3 v)
            {
                float mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
                if (mag == 0)
                    return Vector3::Zero();
                return v / mag;
            }

            static inline Vector3 Orthogonal(Vector3 v)
            {
                return v.z < v.x ?
                    Vector3(v.y, -v.x, 0) : Vector3(0, -v.z, v.y);
            }

            static inline float SqrMagnitude(Vector3 v)
            {
                return v.x * v.x + v.y * v.y + v.z * v.z;
            }
        };


        inline Vector3 operator+(Vector3 lhs, const Vector3 rhs)
        {
            return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
        }

        inline Vector3 operator*(Vector3 lhs, const float rhs)
        {
            return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
        }
#   endif
#else
#   include "Vector3.h"
#endif


struct Quaternion
{
    union
    {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
        float data[4];
    };


    /**
     * Constructors.
     */
    inline Quaternion();
    inline Quaternion(float data[]);
    inline Quaternion(Vector3 vector, float scalar);
    inline Quaternion(float x, float y, float z, float w);


    /**
     * Constants for common quaternions.
     */
    static inline Quaternion Identity();


    /**
     * Returns the angle between two quaternions.
     * The quaternions must be normalized.
     * @param a: The first quaternion.
     * @param b: The second quaternion.
     * @return: A scalar value.
     */
    static inline float Angle(Quaternion a, Quaternion b);

    /**
     * Returns the conjugate of a quaternion.
     * @param rotation: The quaternion in question.
     * @return: A new quaternion.
     */
    static inline Quaternion Conjugate(Quaternion rotation);

    /**
     * Returns the dot product of two quaternions.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A scalar value.
     */
    static inline float Dot(Quaternion lhs, Quaternion rhs);

    /**
     * Creates a new quaternion from the angle-axis representation of
     * a rotation.
     * @param angle: The rotation angle in radians.
     * @param axis: The vector about which the rotation occurs.
     * @return: A new quaternion.
     */
    static inline Quaternion FromAngleAxis(float angle, Vector3 axis);

    /**
     * Create a new quaternion from the euler angle representation of
     * a rotation. The z, x and y values represent rotations about those
     * axis in that respective order.
     * @param rotation: The x, y and z rotations.
     * @return: A new quaternion.
     */
    static inline Quaternion FromEuler(Vector3 rotation);

    /**
     * Create a new quaternion from the euler angle representation of
     * a rotation. The z, x and y values represent rotations about those
     * axis in that respective order.
     * @param x: The rotation about the x-axis in radians.
     * @param y: The rotation about the y-axis in radians.
     * @param z: The rotation about the z-axis in radians.
     * @return: A new quaternion.
     */
    static inline Quaternion FromEuler(float x, float y, float z);

    /**
     * Create a quaternion rotation which rotates "fromVector" to "toVector".
     * @param fromVector: The vector from which to start the rotation.
     * @param toVector: The vector at which to end the rotation.
     * @return: A new quaternion.
     */
    static inline Quaternion FromToRotation(Vector3 fromVector,
                                            Vector3 toVector);

    /**
     * Returns the inverse of a rotation.
     * @param rotation: The quaternion in question.
     * @return: A new quaternion.
     */
    static inline Quaternion Inverse(Quaternion rotation);

    /**
     * Interpolates between a and b by t, which is clamped to the range [0-1].
     * The result is normalized before being returned.
     * @param a: The starting rotation.
     * @param b: The ending rotation.
     * @return: A new quaternion.
     */
    static inline Quaternion Lerp(Quaternion a, Quaternion b, float t);

    /**
     * Interpolates between a and b by t. This normalizes the result when
     * complete.
     * @param a: The starting rotation.
     * @param b: The ending rotation.
     * @param t: The interpolation value.
     * @return: A new quaternion.
     */
    static inline Quaternion LerpUnclamped(Quaternion a, Quaternion b,
                                           float t);

    /**
     * Creates a rotation with the specified forward direction. This is the
     * same as calling LookRotation with (0, 1, 0) as the upwards vector.
     * The output is undefined for parallel vectors.
     * @param forward: The forward direction to look toward.
     * @return: A new quaternion.
     */
    static inline Quaternion LookRotation(Vector3 forward);

    /**
     * Creates a rotation with the specified forward and upwards directions.
     * The output is undefined for parallel vectors.
     * @param forward: The forward direction to look toward.
     * @param upwards: The direction to treat as up.
     * @return: A new quaternion.
     */
    static inline Quaternion LookRotation(Vector3 forward, Vector3 upwards);

    /**
     * Returns the norm of a quaternion.
     * @param rotation: The quaternion in question.
     * @return: A scalar value.
     */
    static inline float Norm(Quaternion rotation);

    /**
     * Returns a quaternion with identical rotation and a norm of one.
     * @param rotation: The quaternion in question.
     * @return: A new quaternion.
     */
    static inline Quaternion Normalized(Quaternion rotation);

    /**
     * Returns a new Quaternion created by rotating "from" towards "to" by
     * "maxRadiansDelta". This will not overshoot, and if a negative delta is
     * applied, it will rotate till completely opposite "to" and then stop.
     * @param from: The rotation at which to start.
     * @param to: The rotation at which to end.
     # @param maxRadiansDelta: The maximum number of radians to rotate.
     * @return: A new Quaternion.
     */
    static inline Quaternion RotateTowards(Quaternion from, Quaternion to,
                                           float maxRadiansDelta);

    /**
     * Returns a new quaternion interpolated between a and b, using spherical
     * linear interpolation. The variable t is clamped to the range [0-1]. The
     * resulting quaternion will be normalized.
     * @param a: The starting rotation.
     * @param b: The ending rotation.
     * @param t: The interpolation value.
     * @return: A new quaternion.
     */
    static inline Quaternion Slerp(Quaternion a, Quaternion b, float t);

    /**
     * Returns a new quaternion interpolated between a and b, using spherical
     * linear interpolation. The resulting quaternion will be normalized.
     * @param a: The starting rotation.
     * @param b: The ending rotation.
     * @param t: The interpolation value.
     * @return: A new quaternion.
     */
    static inline Quaternion SlerpUnclamped(Quaternion a, Quaternion b,
                                            float t);

    /**
     * Outputs the angle axis representation of the provided quaternion.
     * @param rotation: The input quaternion.
     * @param angle: The output angle.
     * @param axis: The output axis.
     */
    static inline void ToAngleAxis(Quaternion rotation, float &angle,
                                   Vector3 &axis);

    /**
     * Returns the Euler angle representation of a rotation. The resulting
     * vector contains the rotations about the z, x and y axis, in that order.
     * @param rotation: The quaternion to convert.
     * @return: A new vector.
     */
    static inline Vector3 ToEuler(Quaternion rotation);

    /**
     * Operator overloading.
     */
    inline struct Quaternion& operator+=(const float rhs);
    inline struct Quaternion& operator-=(const float rhs);
    inline struct Quaternion& operator*=(const float rhs);
    inline struct Quaternion& operator/=(const float rhs);
    inline struct Quaternion& operator+=(const Quaternion rhs);
    inline struct Quaternion& operator-=(const Quaternion rhs);
    inline struct Quaternion& operator*=(const Quaternion rhs);
};

inline Quaternion operator-(Quaternion rhs);
inline Quaternion operator+(Quaternion lhs, const float rhs);
inline Quaternion operator-(Quaternion lhs, const float rhs);
inline Quaternion operator*(Quaternion lhs, const float rhs);
inline Quaternion operator/(Quaternion lhs, const float rhs);
inline Quaternion operator+(const float lhs, Quaternion rhs);
inline Quaternion operator-(const float lhs, Quaternion rhs);
inline Quaternion operator*(const float lhs, Quaternion rhs);
inline Quaternion operator/(const float lhs, Quaternion rhs);
inline Quaternion operator+(Quaternion lhs, const Quaternion rhs);
inline Quaternion operator-(Quaternion lhs, const Quaternion rhs);
inline Quaternion operator*(Quaternion lhs, const Quaternion rhs);
inline Vector3 operator*(Quaternion lhs, const Vector3 rhs);
inline bool operator==(const Quaternion lhs, const Quaternion rhs);
inline bool operator!=(const Quaternion lhs, const Quaternion rhs);



/*******************************************************************************
 * Implementation
 */

Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {}
Quaternion::Quaternion(float data[]) : x(data[0]), y(data[1]), z(data[2]),
                                       w(data[3]) {}
Quaternion::Quaternion(Vector3 vector, float scalar) : x(vector.x),
                                                       y(vector.y), z(vector.z), w(scalar) {}
Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y),
                                                             z(z), w(w) {}



Quaternion Quaternion::Identity() { return Quaternion(0, 0, 0, 1); }


float Quaternion::Angle(Quaternion a, Quaternion b)
{
    float dot = Dot(a, b);
    return acos(fmin(fabs(dot), 1)) * 2;
}

Quaternion Quaternion::Conjugate(Quaternion rotation)
{
    return Quaternion(-rotation.x, -rotation.y, -rotation.z, rotation.w);
}

float Quaternion::Dot(Quaternion lhs, Quaternion rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

Quaternion Quaternion::FromAngleAxis(float angle, Vector3 axis)
{
    Quaternion q;
    float m = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    float s = sin(angle / 2) / m;
    q.x = axis.x * s;
    q.y = axis.y * s;
    q.z = axis.z * s;
    q.w = cos(angle / 2);
    return q;
}

Quaternion Quaternion::FromEuler(Vector3 rotation)
{
    return FromEuler(rotation.x, rotation.y, rotation.z);
}

Quaternion Quaternion::FromEuler(float x, float y, float z)
{
    float cx = cos(x * 0.5);
    float cy = cos(y * 0.5);
    float cz = cos(z * 0.5);
    float sx = sin(x * 0.5);
    float sy = sin(y * 0.5);
    float sz = sin(z * 0.5);
    Quaternion q;
    q.x = cx * sy * sz + cy * cz * sx;
    q.y = cx * cz * sy - cy * sx * sz;
    q.z = cx * cy * sz - cz * sx * sy;
    q.w = sx * sy * sz + cx * cy * cz;
    return q;
}

Quaternion Quaternion::FromToRotation(Vector3 fromVector, Vector3 toVector)
{
    float dot = Vector3::Dot(fromVector, toVector);
    float k = sqrt(Vector3::SqrMagnitude(fromVector) *
                   Vector3::SqrMagnitude(toVector));
    if (fabs(dot / k + 1) < 0.00001)
    {
        Vector3 ortho = Vector3::Orthogonal(fromVector);
        return Quaternion(Vector3::Normalized(ortho), 0);
    }
    Vector3 cross = Vector3::Cross(fromVector, toVector);
    return Normalized(Quaternion(cross, dot + k));
}

Quaternion Quaternion::Inverse(Quaternion rotation)
{
    float n = Norm(rotation);
    return Conjugate(rotation) / (n * n);
}

Quaternion Quaternion::Lerp(Quaternion a, Quaternion b, float t)
{
    if (t < 0) return Normalized(a);
    else if (t > 1) return Normalized(b);
    return LerpUnclamped(a, b, t);
}

Quaternion Quaternion::LerpUnclamped(Quaternion a, Quaternion b, float t)
{
    Quaternion quaternion;
    if (Dot(a, b) >= 0)
        quaternion = a * (1 - t) + b * t;
    else
        quaternion = a * (1 - t) - b * t;
    return Normalized(quaternion);
}

Quaternion Quaternion::LookRotation(Vector3 forward)
{
    return LookRotation(forward, Vector3(0, 1, 0));
}

Quaternion Quaternion::LookRotation(Vector3 forward, Vector3 upwards)
{
    // Normalize inputs
    forward = Vector3::Normalized(forward);
    upwards = Vector3::Normalized(upwards);
    // Don't allow zero vectors
    if (Vector3::SqrMagnitude(forward) < SMALL_float || Vector3::SqrMagnitude(upwards) < SMALL_float)
        return Quaternion::Identity();
    // Handle alignment with up direction
    if (1 - fabs(Vector3::Dot(forward, upwards)) < SMALL_float)
        return FromToRotation(Vector3::Forward(), forward);
    // Get orthogonal vectors
    Vector3 right = Vector3::Normalized(Vector3::Cross(upwards, forward));
    upwards = Vector3::Cross(forward, right);
    // Calculate rotation
    Quaternion quaternion;
    float radicand = right.x + upwards.y + forward.z;
    if (radicand > 0)
    {
        quaternion.w = sqrt(1.0 + radicand) * 0.5;
        float recip = 1.0 / (4.0 * quaternion.w);
        quaternion.x = (upwards.z - forward.y) * recip;
        quaternion.y = (forward.x - right.z) * recip;
        quaternion.z = (right.y - upwards.x) * recip;
    }
    else if (right.x >= upwards.y && right.x >= forward.z)
    {
        quaternion.x = sqrt(1.0 + right.x - upwards.y - forward.z) * 0.5;
        float recip = 1.0 / (4.0 * quaternion.x);
        quaternion.w = (upwards.z - forward.y) * recip;
        quaternion.z = (forward.x + right.z) * recip;
        quaternion.y = (right.y + upwards.x) * recip;
    }
    else if (upwards.y > forward.z)
    {
        quaternion.y = sqrt(1.0 - right.x + upwards.y - forward.z) * 0.5;
        float recip = 1.0 / (4.0 * quaternion.y);
        quaternion.z = (upwards.z + forward.y) * recip;
        quaternion.w = (forward.x - right.z) * recip;
        quaternion.x = (right.y + upwards.x) * recip;
    }
    else
    {
        quaternion.z = sqrt(1.0 - right.x - upwards.y + forward.z) * 0.5;
        float recip = 1.0 / (4.0 * quaternion.z);
        quaternion.y = (upwards.z + forward.y) * recip;
        quaternion.x = (forward.x + right.z) * recip;
        quaternion.w = (right.y - upwards.x) * recip;
    }
    return quaternion;
}

float Quaternion::Norm(Quaternion rotation)
{
    return sqrt(rotation.x * rotation.x +
                rotation.y * rotation.y +
                rotation.z * rotation.z +
                rotation.w * rotation.w);
}

Quaternion Quaternion::Normalized(Quaternion rotation)
{
    return rotation / Norm(rotation);
}

Quaternion Quaternion::RotateTowards(Quaternion from, Quaternion to,
                                     float maxRadiansDelta)
{
    float angle = Quaternion::Angle(from, to);
    if (angle == 0)
        return to;
    maxRadiansDelta = fmax(maxRadiansDelta, angle - M_PI);
    float t = fmin(1, maxRadiansDelta / angle);
    return Quaternion::SlerpUnclamped(from, to, t);
}

Quaternion Quaternion::Slerp(Quaternion a, Quaternion b, float t)
{
    if (t < 0) return Normalized(a);
    else if (t > 1) return Normalized(b);
    return SlerpUnclamped(a, b, t);
}

Quaternion Quaternion::SlerpUnclamped(Quaternion a, Quaternion b, float t)
{
    float n1;
    float n2;
    float n3 = Dot(a, b);
    bool flag = false;
    if (n3 < 0)
    {
        flag = true;
        n3 = -n3;
    }
    if (n3 > 0.999999)
    {
        n2 = 1 - t;
        n1 = flag ? -t : t;
    }
    else
    {
        float n4 = acos(n3);
        float n5 = 1 / sin(n4);
        n2 = sin((1 - t) * n4) * n5;
        n1 = flag ? -sin(t * n4) * n5 : sin(t * n4) * n5;
    }
    Quaternion quaternion;
    quaternion.x = (n2 * a.x) + (n1 * b.x);
    quaternion.y = (n2 * a.y) + (n1 * b.y);
    quaternion.z = (n2 * a.z) + (n1 * b.z);
    quaternion.w = (n2 * a.w) + (n1 * b.w);
    return Normalized(quaternion);
}

void Quaternion::ToAngleAxis(Quaternion rotation, float &angle, Vector3 &axis)
{
    if (rotation.w > 1)
        rotation = Normalized(rotation);
    angle = 2 * acos(rotation.w);
    float s = sqrt(1 - rotation.w * rotation.w);
    if (s < 0.00001) {
        axis.x = 1;
        axis.y = 0;
        axis.z = 0;
    } else {
        axis.x = rotation.x / s;
        axis.y = rotation.y / s;
        axis.z = rotation.z / s;
    }
}

Vector3 Quaternion::ToEuler(Quaternion rotation)
{
    float sqw = rotation.w * rotation.w;
    float sqx = rotation.x * rotation.x;
    float sqy = rotation.y * rotation.y;
    float sqz = rotation.z * rotation.z;
    // If normalized is one, otherwise is correction factor
    float unit = sqx + sqy + sqz + sqw;
    float test = rotation.x * rotation.w - rotation.y * rotation.z;
    Vector3 v;
    // Singularity at north pole
    if (test > 0.4995f * unit)
    {
        v.y = 2 * atan2(rotation.y, rotation.x);
        v.x = M_PI_2;
        v.z = 0;
        return v;
    }
    // Singularity at south pole
    if (test < -0.4995f * unit)
    {
        v.y = -2 * atan2(rotation.y, rotation.x);
        v.x = -M_PI_2;
        v.z = 0;
        return v;
    }
    // Yaw
    v.y = atan2(2 * rotation.w * rotation.y + 2 * rotation.z * rotation.x,
                1 - 2 * (rotation.x * rotation.x + rotation.y * rotation.y));
    // Pitch
    v.x = asin(2 * (rotation.w * rotation.x - rotation.y * rotation.z));
    // Roll
    v.z = atan2(2 * rotation.w * rotation.z + 2 * rotation.x * rotation.y,
                1 - 2 * (rotation.z * rotation.z + rotation.x * rotation.x));
    return  (v * Rad2Deg) + 180;
}

struct Quaternion& Quaternion::operator+=(const float rhs)
{
    x += rhs;
    y += rhs;
    z += rhs;
    w += rhs;
    return *this;
}

struct Quaternion& Quaternion::operator-=(const float rhs)
{
    x -= rhs;
    y -= rhs;
    z -= rhs;
    w -= rhs;
    return *this;
}

struct Quaternion& Quaternion::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

struct Quaternion& Quaternion::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

struct Quaternion& Quaternion::operator+=(const Quaternion rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

struct Quaternion& Quaternion::operator-=(const Quaternion rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

struct Quaternion& Quaternion::operator*=(const Quaternion rhs)
{
    Quaternion q;
    q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    q.x = x * rhs.w + w * rhs.x + y * rhs.z - z * rhs.y;
    q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
    q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
    *this = q;
    return *this;
}

Quaternion operator-(Quaternion rhs) { return rhs * -1; }
Quaternion operator+(Quaternion lhs, const float rhs) { return lhs += rhs; }
Quaternion operator-(Quaternion lhs, const float rhs) { return lhs -= rhs; }
Quaternion operator*(Quaternion lhs, const float rhs) { return lhs *= rhs; }
Quaternion operator/(Quaternion lhs, const float rhs) { return lhs /= rhs; }
Quaternion operator+(const float lhs, Quaternion rhs) { return rhs += lhs; }
Quaternion operator-(const float lhs, Quaternion rhs) { return rhs -= lhs; }
Quaternion operator*(const float lhs, Quaternion rhs) { return rhs *= lhs; }
Quaternion operator/(const float lhs, Quaternion rhs) { return rhs /= lhs; }
Quaternion operator+(Quaternion lhs, const Quaternion rhs)
{
    return lhs += rhs;
}
Quaternion operator-(Quaternion lhs, const Quaternion rhs)
{
    return lhs -= rhs;
}
Quaternion operator*(Quaternion lhs, const Quaternion rhs)
{
    return lhs *= rhs;
}

Vector3 operator*(Quaternion lhs, const Vector3 rhs)
{
    Vector3 u = Vector3(lhs.x, lhs.y, lhs.z);
    float s = lhs.w;
    return u * (Vector3::Dot(u, rhs) * 2)
           + rhs * (s * s - Vector3::Dot(u, u))
           + Vector3::Cross(u, rhs) * (2.0 * s);
}

bool operator==(const Quaternion lhs, const Quaternion rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y &&
           lhs.z == rhs.z &&
           lhs.w == rhs.w;
}

bool operator!=(const Quaternion lhs, const Quaternion rhs)
{
    return !(lhs == rhs);
}
