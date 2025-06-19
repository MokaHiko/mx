#ifndef MX_MATH_H_
#define MX_MATH_H_

#include "mx/mx.h"
#include "mx/mx_math_types.h"
#include <math.h>

#define MX_PI              (real_t)3.1415927
#define MX_DEG_TO_RAD(deg) ((deg) * (MX_PI / (real_t)180.0))
#define MX_RAD_TO_DEG(rad) ((rad) * ((real_t)180.0 / MX_PI))

#ifdef __cplusplus
extern "C" {
#endif

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
MX_API MX_NO_DISCARD real_t mx_clamp(real_t val, real_t min, real_t max);

/**
 * @brief Performs linear interpolation between a and b by factor t.
 *
 * @param a The start value.
 * @param b The end value.
 * @param t The interpolation factor (typically in [0, 1]).
 * @return The interpolated value: a + (b - a) * t.
 */
MX_API MX_NO_DISCARD real_t mx_lerpf(float a, float b, float t);

MX_API MX_NO_DISCARD mx_vec3 mx_vec3_norm(mx_vec3 a);

MX_NO_DISCARD static inline mx_bool mx_vec3_eqv(mx_vec3 left, mx_vec3 right) {
    return left.x == right.x && left.y == right.y && left.z == right.z;
}

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
 * @return The resulting vector (a × b).
 */
MX_API MX_NO_DISCARD mx_vec3 mx_vec3_cross(mx_vec3 a, mx_vec3 b);

MX_API MX_NO_DISCARD mx_vec3 mx_vec3_scale(mx_vec3 a, float s);
/**
 * @brief Adds two 3D vectors.
 *
 * @param a The first input vector.
 * @param b The second input vector.
 * @return The resulting vector (a + b).
 */
MX_API MX_NO_DISCARD mx_vec3 mx_vec3_add(mx_vec3 a, mx_vec3 b);

/**
 * @brief Subtracts vector b from vector a.
 *
 * @param a The first input vector.
 * @param b The vector to subtract.
 * @return The resulting vector (a - b).
 */
MX_API MX_NO_DISCARD mx_vec3 mx_vec3_sub(mx_vec3 a, mx_vec3 b);

/**
 * @brief Multiplies two 3D vectors component-wise.
 *
 * @param a The first input vector.
 * @param b The second input vector.
 * @return The resulting vector (a * b).
 */
MX_API MX_NO_DISCARD mx_vec3 mx_vec3_mul(mx_vec3 a, mx_vec3 b);

MX_API MX_NO_DISCARD mx_ivec3 mx_ivec3_scale(mx_ivec3 a, int s);

/**
 * @brief Adds two 3D vectors.
 *
 * @param a The first input vector.
 * @param b The second input vector.
 * @return The resulting vector (a + b).
 */
MX_API MX_NO_DISCARD mx_ivec3 mx_ivec3_add(mx_ivec3 a, mx_ivec3 b);

/**
 * @brief Subtracts vector b from vector a.
 *
 * @param a The first input vector.
 * @param b The vector to subtract.
 * @return The resulting vector (a - b).
 */
MX_API MX_NO_DISCARD mx_ivec3 mx_ivec3_sub(mx_ivec3 a, mx_ivec3 b);

/**
 * @brief Multiplies two 3D vectors component-wise.
 *
 * @param a The first input vector.
 * @param b The second input vector.
 * @return The resulting vector (a * b).
 */
MX_API MX_NO_DISCARD mx_ivec3 mx_ivec3_mul(mx_ivec3 a, mx_ivec3 b);

MX_NO_DISCARD static inline real_t mx_vec4_dot(mx_vec4 left, mx_vec4 right) {
    float result;

    // note(zak): in the future if we wanna check what version sse is support
    // we can use _mm_dp_ps (4.3) but for now we will use the old way.
    // or a r = _mm_mul_ps(v1, v2), r = _mm_hadd_ps(r, r), r = _mm_hadd_ps(r, r) for sse3
#ifdef handmade_math__use_sse
    __m128 sseresultone = _mm_mul_ps(left.sse, right.sse);
    __m128 sseresulttwo = _mm_shuffle_ps(sseresultone, sseresultone, _mm_shuffle(2, 3, 0, 1));
    sseresultone = _mm_add_ps(sseresultone, sseresulttwo);
    sseresulttwo = _mm_shuffle_ps(sseresultone, sseresultone, _mm_shuffle(0, 1, 2, 3));
    sseresultone = _mm_add_ps(sseresultone, sseresulttwo);
    _mm_store_ss(&result, sseresultone);
#elif defined(handmade_math__use_neon)
    float32x4_t neonmultiplyresult = vmulq_f32(left.neon, right.neon);
    float32x4_t neonhalfadd = vpaddq_f32(neonmultiplyresult, neonmultiplyresult);
    float32x4_t neonfulladd = vpaddq_f32(neonhalfadd, neonhalfadd);
    result = vgetq_lane_f32(neonfulladd, 0);
#else
    result = ((left.x * right.x) + (left.z * right.z)) + ((left.y * right.y) + (left.w * right.w));
#endif

    return result;
}

MX_NO_DISCARD static inline mx_vec4 mx_mulv4f(mx_vec4 left, float right) {
    mx_vec4 result;

#ifdef mx_math__use_sse
    __m128 scalar = _mm_set1_ps(right);
    result.sse = _mm_mul_ps(left.sse, scalar);
#elif defined(handmade_math__use_neon)
    result.neon = vmulq_n_f32(left.neon, right);
#else
    result.x = left.x * right;
    result.y = left.y * right;
    result.z = left.z * right;
    result.w = left.w * right;
#endif

    return result;
}

static inline float mx_sqrt(real_t a) {
    float result;

#ifdef handmade_math__use_sse
    __m128 in = _mm_set_ss(float);
    __m128 out = _mm_sqrt_ss(in);
    result = _mm_cvtss_f32(out);
#elif defined(handmade_math__use_neon)
    float32x4_t in = vdupq_n_f32(float);
    float32x4_t out = vsqrtq_f32(in);
    result = vgetq_lane_f32(out, 0);
#else
    result = sqrtf(a);
#endif

    return result;
}

MX_NO_DISCARD static inline float mx_invsqrt(real_t a) {
    float result;

    result = 1.0f / mx_sqrt(a);

    return result;
}

MX_NO_DISCARD static inline mx_vec4 mx_vec4_norm(mx_vec4 a) {
    return mx_mulv4f(a, mx_invsqrt(mx_vec4_dot(a, a)));
};

MX_NO_DISCARD static inline mx_vec4 mx_vec4_scale(mx_vec4 a, float s) {
    return (mx_vec4) { a.x* s, a.y* s, a.z* s, a.w* s };
}

MX_NO_DISCARD static inline mx_quat mx_quat_norm(mx_quat quat) {
    mx_vec4 vec = {quat.x, quat.y, quat.z, quat.w};
    vec = mx_vec4_norm(vec);
    mx_quat result = {vec.x, vec.y, vec.z, vec.w};
    return result;
}

#ifdef __cplusplus
}
#endif /*MX_MATH_MTX_H */

#endif
