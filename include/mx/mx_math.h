#ifndef MX_MATH_H_
#define MX_MATH_H_

#include "mx/mx.h"
#include "mx/mx_math_types.h"

#define MX_PI (real_t)3.1415927
#define MX_DEG_TO_RAD(deg) ((deg) * (MX_PI / (real_t)180.0))
#define MX_RAD_TO_DEG(rad) ((rad) * ((real_t)180.0 / MX_PI))

MX_API MX_NO_DISCARD real_t mx_sin(real_t radians);
MX_API MX_NO_DISCARD real_t mx_cos(real_t radians);
MX_API MX_NO_DISCARD real_t mx_tan(real_t radians);
MX_API MX_NO_DISCARD real_t mx_pow(real_t base, real_t n);

/**
 * @brief Clamps a floating-point value between a minimum and maximum.
 *
 * @param val The value to clamp.
 * @param min The lower bound.
 * @param max The upper bound.
 * @return The clamped value: min if val < min, max if val > max, otherwise val.
 */
MX_API MX_NO_DISCARD real_t mx_clampf(float val, float min, float max);

/**
 * @brief Performs linear interpolation between a and b by factor t.
 *
 * @param a The start value.
 * @param b The end value.
 * @param t The interpolation factor (typically in [0, 1]).
 * @return The interpolated value: a + (b - a) * t.
 */
MX_API MX_NO_DISCARD real_t mx_lerpf(float a, float b, float t);

MX_API void mx_vec3_norm(const mx_vec3 a, mx_vec3 out);

/**
 * @brief Computes the dot product of two 3D vectors.
 *
 * @param a The first input vector.
 * @param b The second input vector.
 * @return The scalar dot product (a · b).
 */
MX_API MX_NO_DISCARD real_t mx_vec3_dot(const mx_vec3 a, const mx_vec3 b);

/**
 * @brief Computes the squared length of a 3D vector.
 *
 * @param a The input vector.
 * @return The squared length (||a||²), i.e., a.x² + a.y² + a.z².
 */
MX_API MX_NO_DISCARD real_t mx_vec3_len_2(const mx_vec3 a);

/**
 * @brief Computes the length (magnitude) of a 3D vector.
 *
 * @param a The input vector.
 * @return The length ||a|| = sqrt(a.x² + a.y² + a.z²).
 */
MX_API MX_NO_DISCARD real_t mx_vec3_len(const mx_vec3 a);

/**
 * @brief Computes the cross product of two 3D vectors.
 *
 * @param a The first input vector.
 * @param b The second input vector.
 * @param out The resulting vector (a × b).
 */
MX_API void mx_vec3_cross(const mx_vec3 a, const mx_vec3 b, mx_vec3 out);

MX_API void mx_vec3_scale(const mx_vec3 a, float s, mx_vec3 out);

/**
 * @brief Adds two 3D vectors.
 *
 * @param a The first input vector.
 * @param b The second input vector.
 * @param out The resulting vector (a + b).
 */
MX_API void mx_vec3_add(const mx_vec3 a, const mx_vec3 b, mx_vec3 out);

/**
 * @brief Subtracts vector b from vector a.
 *
 * @param a The first input vector.
 * @param b The vector to subtract.
 * @param out The resulting vector (a - b).
 */
MX_API void mx_vec3_sub(const mx_vec3 a, const mx_vec3 b, mx_vec3 out);

/**
 * @brief Subtracts vector b from vector a (in-place).
 *
 * @param a The vector to be modified (a -= b).
 * @param b The vector to subtract.
 */
MX_API void mx_vec3_sub_into(mx_vec3 a, const mx_vec3 b);

/**
 * @brief Multiplies two 3D vectors component-wise.
 *
 * @param a The first input vector.
 * @param b The second input vector.
 * @param out The resulting vector (a * b).
 */
MX_API void mx_vec3_mul(const mx_vec3 a, const mx_vec3 b, mx_vec3 out);


MX_API void mx_ivec3_scale(const mx_ivec3 a, int s, mx_ivec3 out);

/**
 * @brief Adds two 3D vectors.
 *
 * @param a The first input vector.
 * @param b The second input vector.
 * @param out The resulting vector (a + b).
 */
MX_API void mx_ivec3_add(const mx_ivec3 a, const mx_ivec3 b, mx_ivec3 out);

/**
 * @brief Subtracts vector b from vector a.
 *
 * @param a The first input vector.
 * @param b The vector to subtract.
 * @param out The resulting vector (a - b).
 */
MX_API void mx_ivec3_sub(const mx_ivec3 a, const mx_ivec3 b, mx_ivec3 out);

/**
 * @brief Subtracts vector b from vector a (in-place).
 *
 * @param a The vector to be modified (a -= b).
 * @param b The vector to subtract.
 */
MX_API void mx_ivec3_sub_into(mx_ivec3 a, const mx_ivec3 b);

/**
 * @brief Multiplies two 3D vectors component-wise.
 *
 * @param a The first input vector.
 * @param b The second input vector.
 * @param out The resulting vector (a * b).
 */
MX_API void mx_ivec3_mul(const mx_ivec3 a, const mx_ivec3 b, mx_ivec3 out);

#endif
