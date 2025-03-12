#pragma once

#include <math.h>

using namespace std;

struct vec3 {
    float x, y, z;

    vec3() : x(0), y(0), z(0) {};
    vec3(float x, float y, float z) : x(x), y(y), z(z) {};

    /**
     * @brief 3D vector addition
     *
     * @param v the vector to add
     * @return a new vector with the elements of this vector and v added together
     */
    vec3 operator+(const vec3& v) const {
        return vec3(x + v.x, y + v.y, z + v.z);
    }

    /**
     * @brief 3D vector addition (inplace)
     *
     * @param v the vector to add
     * @return a reference to this vector, with the elements of this vector and v added together
     */
    vec3 operator+=(const vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    /**
     * @brief 3D vector subtraction
     *
     * @param v the vector to subtract
     * @return a new vector with the elements of this vector and v subtracted
     */
    vec3 operator-(const vec3& v) const {
        return vec3(x - v.x, y - v.y, z - v.z);
    }

    /**
     * @brief 3D vector subtraction (inplace)
     *
     * @param v the vector to subtract
     * @return a reference to this vector, with the elements of this vector and v subtracted
     */
    vec3 operator-=(const vec3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    /**
     * @brief 3D vector scalar multiplication
     *
     * @param f the factor to multiply with
     * @return a new vector with the elements of this vector scaled by f
     */
    vec3 operator*(float f) const {
        return vec3(x*f, y*f, z*f);
    }

    /**
     * @brief 3D vector scalar multiplication (inplace)
     *
     * @param f the factor to multiply with
     * @return a reference to this vector, with the elements of this vector scaled by f
     */
    vec3 operator*=(float f) {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    /**
     * @brief 3D vector scalar division
     *
     * @param f the factor to divide by
     * @return a new vector with the elements of this vector divided by f
     */
    vec3 operator/(float f) const {
        return vec3(x/f, y/f, z/f);
    }

    /**
     * @brief 3D vector scalar division (inplace)
     *
     * @param f the factor to divide by
     * @return a reference to this vector, with the elements of this vector divided by f
     */
    vec3 operator/=(float f) {
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }

    /**
     * @brief 3D vector dot product
     *
     * @param v the vector to calculate the dot product with
     * @return the dot product of this vector and v
     */
    float operator*(const vec3& v) const {
        return x*v.x + y*v.y + z*v.z;
    }

    /**
     * @brief 3D vector cross product
     *
     * @param v the vector to calculate the cross product with
     * @return a new vector that is the cross product of this vector and v
     */

    vec3 cross(const vec3& v) const {
        return vec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }

/**
 * @brief Calculate the magnitude (length) of the vector
 *
 * @return The magnitude of the vector
 */

    float magnitude() const {
        return sqrt(x*x + y*y + z*z);
    }

    /**
     * @brief Calculate the magnitude (length) of the vector, squared
     *
     * This is slightly more efficient than calling magnitude() as it avoids the square root operation
     *
     * @return The magnitude of the vector, squared
     */
    float magnitudeSquared() const {
        return x*x + y*y + z*z;
    }

    /**
     * @brief Normalise the vector to have a length of 1
     *
     * This modifies the vector in-place. If you want a new vector that is normalised, use the normalised() function
     */
    void normalise() {
        float m = magnitude();
        x /= m;
        y /= m;
        z /= m;
    }

    /**
     * @brief Returns a new vector that is normalised to have a length of 1
     *
     * This does not modify the current vector, but instead returns a new vector that is normalised
     *
     * @return A new vector, normalised to have a length of 1
     */
    vec3 normalised() {
        float m = magnitude();
        return vec3(x/m, y/m, z/m);
    }
};