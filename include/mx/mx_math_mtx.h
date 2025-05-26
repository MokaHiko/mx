#ifndef MX_MATH_MTX_H_
#define MX_MATH_MTX_H_

#include "mx.h"

#include "mx/mx_math.h"
#include "mx_math_types.h"

#define MX_RH
#define MX_RH_ZO

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines a 4x4 matrix (column-major order).
 *
 * The matrix is represented as an array of 16 floating point values (real_t).
 * The matrix elements are arranged as:
 *
 * | m[0]   m[4]   m[8]   m[12] |
 * | m[1]   m[5]   m[9]   m[13] |
 * | m[2]   m[6]   m[10]  m[14] |
 * | m[3]   m[7]   m[11]  m[15] |
 *
 * @note Mx matrices are in column-major order.
 */
typedef union mx_mat4 {
    real_t elements[4][4];
    mx_vec4 columns[4];

    real_t val[16];
} mx_mat4;

static inline mx_mat4 _mat4_diagonal(float diagonal) {
    mx_mat4 result = {0};

    result.elements[0][0] = diagonal;
    result.elements[1][1] = diagonal;
    result.elements[2][2] = diagonal;
    result.elements[3][3] = diagonal;

    return result;
}

/**
 * @brief Identity matrix for a 4x4 matrix (mx_mat4).
 *
 * The identity matrix is defined as:
 *
 * | 1, 0, 0, 0 |
 * | 0, 1, 0, 0 |
 * | 0, 0, 1, 0 |
 * | 0, 0, 0, 1 |
 */
#define MX_MAT4_IDENTITY                                                       \
    (mx_mat4){1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}

MX_API MX_NO_DISCARD static inline mx_vec4 mx_mat_mul_vec4(mx_mat4 left,
                                                           mx_vec4 right) {
    mx_vec4 result;
#ifdef MX_MATH__USE_SSE
    Result.SSE = _mm_mul_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, 0x00),
                            Right.Columns[0].SSE);
    Result.SSE = _mm_add_ps(Result.SSE,
                            _mm_mul_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, 0x55),
                                       Right.Columns[1].SSE));
    Result.SSE = _mm_add_ps(Result.SSE,
                            _mm_mul_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, 0xaa),
                                       Right.Columns[2].SSE));
    Result.SSE = _mm_add_ps(Result.SSE,
                            _mm_mul_ps(_mm_shuffle_ps(Left.SSE, Left.SSE, 0xff),
                                       Right.Columns[3].SSE));
#else
    result.x = right.elements[0] * left.columns[0].x;
    result.y = right.elements[0] * left.columns[0].y;
    result.z = right.elements[0] * left.columns[0].z;
    result.w = right.elements[0] * left.columns[0].w;

    result.x += right.elements[1] * left.columns[1].x;
    result.y += right.elements[1] * left.columns[1].y;
    result.z += right.elements[1] * left.columns[1].z;
    result.w += right.elements[1] * left.columns[1].w;

    result.x += right.elements[2] * left.columns[2].x;
    result.y += right.elements[2] * left.columns[2].y;
    result.z += right.elements[2] * left.columns[2].z;
    result.w += right.elements[2] * left.columns[2].w;

    result.x += right.elements[3] * left.columns[3].x;
    result.y += right.elements[3] * left.columns[3].y;
    result.z += right.elements[3] * left.columns[3].z;
    result.w += right.elements[3] * left.columns[3].w;
#endif

    return result;
}

// SSE definess
static inline mx_vec4 mx_linearcombinev4m4(mx_vec4 left, mx_mat4 right) {
    mx_vec4 result;
#ifdef mx_math__use_sse
    result.sse = _mm_mul_ps(_mm_shuffle_ps(left.sse, left.sse, 0x00),
                            right.columns[0].sse);
    result.sse = _mm_add_ps(result.sse,
                            _mm_mul_ps(_mm_shuffle_ps(left.sse, left.sse, 0x55),
                                       right.columns[1].sse));
    result.sse = _mm_add_ps(result.sse,
                            _mm_mul_ps(_mm_shuffle_ps(left.sse, left.sse, 0xaa),
                                       right.columns[2].sse));
    result.sse = _mm_add_ps(result.sse,
                            _mm_mul_ps(_mm_shuffle_ps(left.sse, left.sse, 0xff),
                                       right.columns[3].sse));
#elif defined(handmade_math__use_neon)
    result.neon = vmulq_laneq_f32(right.columns[0].neon, left.neon, 0);
    result.neon =
        vfmaq_laneq_f32(result.neon, right.columns[1].neon, left.neon, 1);
    result.neon =
        vfmaq_laneq_f32(result.neon, right.columns[2].neon, left.neon, 2);
    result.neon =
        vfmaq_laneq_f32(result.neon, right.columns[3].neon, left.neon, 3);
#else
    result.x = left.elements[0] * right.columns[0].x;
    result.y = left.elements[0] * right.columns[0].y;
    result.z = left.elements[0] * right.columns[0].z;
    result.w = left.elements[0] * right.columns[0].w;

    result.x += left.elements[1] * right.columns[1].x;
    result.y += left.elements[1] * right.columns[1].y;
    result.z += left.elements[1] * right.columns[1].z;
    result.w += left.elements[1] * right.columns[1].w;

    result.x += left.elements[2] * right.columns[2].x;
    result.y += left.elements[2] * right.columns[2].y;
    result.z += left.elements[2] * right.columns[2].z;
    result.w += left.elements[2] * right.columns[2].w;

    result.x += left.elements[3] * right.columns[3].x;
    result.y += left.elements[3] * right.columns[3].y;
    result.z += left.elements[3] * right.columns[3].z;
    result.w += left.elements[3] * right.columns[3].w;
#endif

    return result;
}

/**
 * @brief Multiplies two 4x4 matrices.
 * @return a * b
 */
MX_API MX_NO_DISCARD static inline mx_mat4 mx_mat4_mul(mx_mat4 left,
                                                       mx_mat4 right) {
    mx_mat4 result;

    result.columns[0] = mx_linearcombinev4m4(right.columns[0], left);
    result.columns[1] = mx_linearcombinev4m4(right.columns[1], left);
    result.columns[2] = mx_linearcombinev4m4(right.columns[2], left);
    result.columns[3] = mx_linearcombinev4m4(right.columns[3], left);

    return result;
}

MX_API MX_NO_DISCARD static inline mx_mat4
mx_ortho(float left, float right, float bottom, float top, float n, float f) {
    mx_mat4 result = {0};

    result.elements[0][0] = 2.0f / (right - left);
    result.elements[1][1] = 2.0f / (top - bottom);
    result.elements[2][2] = 1.0f / (n - f);
    result.elements[3][3] = 1.0f;

    result.elements[3][0] = (left + right) / (left - right);
    result.elements[3][1] = (bottom + top) / (bottom - top);
    result.elements[3][2] = (n) / (n - f);

    return result;
}

#ifdef MX_RH_ZO
MX_API MX_NO_DISCARD static inline mx_mat4
mx_perspective(real_t fov, real_t aspect_ratio, real_t n, real_t f) {
    mx_mat4 result = {0};

    // See
    // https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml

    float cotangent = 1.0f / mx_tan(fov / 2.0f);
    result.elements[0][0] = cotangent / aspect_ratio;
    result.elements[1][1] = cotangent;
    result.elements[2][3] = -1.0f;

    result.elements[2][2] = (f) / (n - f);
    result.elements[3][2] = (n * f) / (n - f);

    return result;
}
#endif

static inline mx_mat4 _look_at(mx_vec3 f, mx_vec3 s, mx_vec3 u, mx_vec3 eye) {
    mx_mat4 result;

    result.elements[0][0] = s.x;
    result.elements[0][1] = u.x;
    result.elements[0][2] = -f.x;
    result.elements[0][3] = 0.0f;

    result.elements[1][0] = s.y;
    result.elements[1][1] = u.y;
    result.elements[1][2] = -f.y;
    result.elements[1][3] = 0.0f;

    result.elements[2][0] = s.z;
    result.elements[2][1] = u.z;
    result.elements[2][2] = -f.z;
    result.elements[2][3] = 0.0f;

    result.elements[3][0] = -mx_vec3_dot(s, eye);
    result.elements[3][1] = -mx_vec3_dot(u, eye);
    result.elements[3][2] = mx_vec3_dot(f, eye);
    result.elements[3][3] = 1.0f;

    return result;
}

#ifdef MX_RH
MX_API MX_NO_DISCARD static inline mx_mat4
mx_look_at(mx_vec3 eye, mx_vec3 center, mx_vec3 up) {
    mx_vec3 f = mx_vec3_norm(mx_vec3_sub(center, eye));
    mx_vec3 s = mx_vec3_norm(mx_vec3_cross(f, up));
    mx_vec3 u = mx_vec3_cross(s, f);

    return _look_at(f, s, u, eye);
}
#endif

MX_API MX_NO_DISCARD static inline mx_mat4 mx_translate(mx_vec3 position) {
    mx_mat4 result = _mat4_diagonal(1.0);

    result.elements[3][0] = position.x;
    result.elements[3][1] = position.y;
    result.elements[3][2] = position.z;

    return result;
}

MX_API MX_NO_DISCARD static inline mx_mat4 mx_scale(mx_vec3 scale) {
    mx_mat4 result = _mat4_diagonal(1.0);

    result.elements[0][0] *= scale.x;
    result.elements[1][1] *= scale.y;
    result.elements[2][2] *= scale.z;

    return result;
}

MX_API MX_NO_DISCARD static inline mx_mat4 mx_mat4_rotate_euler(real_t angle,
                                                                mx_vec3 axis) {
    mx_mat4 result = _mat4_diagonal(1.0);
    axis = mx_vec3_norm(axis);

    real_t sintheta = mx_sin(angle);
    real_t costheta = mx_cos(angle);
    real_t cosvalue = 1.0f - costheta;

    result.elements[0][0] = (axis.x * axis.x * cosvalue) + costheta;
    result.elements[0][1] = (axis.x * axis.y * cosvalue) + (axis.z * sintheta);
    result.elements[0][2] = (axis.x * axis.z * cosvalue) - (axis.y * sintheta);

    result.elements[1][0] = (axis.y * axis.x * cosvalue) - (axis.z * sintheta);
    result.elements[1][1] = (axis.y * axis.y * cosvalue) + costheta;
    result.elements[1][2] = (axis.y * axis.z * cosvalue) + (axis.x * sintheta);

    result.elements[2][0] = (axis.z * axis.x * cosvalue) + (axis.y * sintheta);
    result.elements[2][1] = (axis.z * axis.y * cosvalue) - (axis.x * sintheta);
    result.elements[2][2] = (axis.z * axis.z * cosvalue) + costheta;

    return result;
}

MX_API MX_NO_DISCARD static inline mx_mat4 mx_quat_mat4(mx_quat quat) {
    mx_mat4 result;

    mx_quat normalizedq = mx_quat_norm(quat);

    float xx, yy, zz, xy, xz, yz, wx, wy, wz;

    xx = normalizedq.x * normalizedq.x;
    yy = normalizedq.y * normalizedq.y;
    zz = normalizedq.z * normalizedq.z;
    xy = normalizedq.x * normalizedq.y;
    xz = normalizedq.x * normalizedq.z;
    yz = normalizedq.y * normalizedq.z;
    wx = normalizedq.w * normalizedq.x;
    wy = normalizedq.w * normalizedq.y;
    wz = normalizedq.w * normalizedq.z;

    result.elements[0][0] = 1.0f - 2.0f * (yy + zz);
    result.elements[0][1] = 2.0f * (xy + wz);
    result.elements[0][2] = 2.0f * (xz - wy);
    result.elements[0][3] = 0.0f;

    result.elements[1][0] = 2.0f * (xy - wz);
    result.elements[1][1] = 1.0f - 2.0f * (xx + zz);
    result.elements[1][2] = 2.0f * (yz + wx);
    result.elements[1][3] = 0.0f;

    result.elements[2][0] = 2.0f * (xz + wy);
    result.elements[2][1] = 2.0f * (yz - wx);
    result.elements[2][2] = 1.0f - 2.0f * (xx + yy);
    result.elements[2][3] = 0.0f;

    result.elements[3][0] = 0.0f;
    result.elements[3][1] = 0.0f;
    result.elements[3][2] = 0.0f;
    result.elements[3][3] = 1.0f;

    return result;
}

#ifdef __cplusplus
}
#endif

MX_API MX_NO_DISCARD static inline mx_mat4 mx_mat4_transpose(mx_mat4 matrix) {
    mx_mat4 result;
#ifdef HANDMADE_MATH__USE_SSE
    Result = Matrix;
    _MM_TRANSPOSE4_PS(Result.Columns[0].SSE,
                      Result.Columns[1].SSE,
                      Result.Columns[2].SSE,
                      Result.Columns[3].SSE);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4x4_t Transposed = vld4q_f32((float*)Matrix.Columns);
    Result.Columns[0].NEON = Transposed.val[0];
    Result.Columns[1].NEON = Transposed.val[1];
    Result.Columns[2].NEON = Transposed.val[2];
    Result.Columns[3].NEON = Transposed.val[3];
#else
    result.elements[0][0] = matrix.elements[0][0];
    result.elements[0][1] = matrix.elements[1][0];
    result.elements[0][2] = matrix.elements[2][0];
    result.elements[0][3] = matrix.elements[3][0];
    result.elements[1][0] = matrix.elements[0][1];
    result.elements[1][1] = matrix.elements[1][1];
    result.elements[1][2] = matrix.elements[2][1];
    result.elements[1][3] = matrix.elements[3][1];
    result.elements[2][0] = matrix.elements[0][2];
    result.elements[2][1] = matrix.elements[1][2];
    result.elements[2][2] = matrix.elements[2][2];
    result.elements[2][3] = matrix.elements[3][2];
    result.elements[3][0] = matrix.elements[0][3];
    result.elements[3][1] = matrix.elements[1][3];
    result.elements[3][2] = matrix.elements[2][3];
    result.elements[3][3] = matrix.elements[3][3];
#endif

    return result;
}

static inline mx_vec4 mx_v4v(mx_vec3 v, real_t w) {
    mx_vec4 result;

#ifdef MX_MATH__USE_SSE
    Result.SSE = _mm_setr_ps(Vector.X, Vector.Y, Vector.Z, W);
#elif defined(HANDMADE_MATH__USE_NEON)
    float32x4_t v = {Vector.X, Vector.Y, Vector.Z, W};
    Result.NEON = v;
#else
    result.xyz = v;
    result.w = w;
#endif

    return result;
}

MX_API MX_NO_DISCARD static inline mx_mat4 mx_mat4_inverse(mx_mat4 matrix) {
    mx_vec3 c01 = mx_vec3_cross(matrix.columns[0].xyz, matrix.columns[1].xyz);
    mx_vec3 c23 = mx_vec3_cross(matrix.columns[2].xyz, matrix.columns[3].xyz);
    mx_vec3 b10 =
        mx_vec3_sub(mx_vec3_scale(matrix.columns[0].xyz, matrix.columns[1].w),
                    mx_vec3_scale(matrix.columns[1].xyz, matrix.columns[0].w));
    mx_vec3 b32 =
        mx_vec3_sub(mx_vec3_scale(matrix.columns[2].xyz, matrix.columns[3].w),
                    mx_vec3_scale(matrix.columns[3].xyz, matrix.columns[2].w));

    float invdeterminant =
        1.0f / (mx_vec3_dot(c01, b32) + mx_vec3_dot(c23, b10));
    c01 = mx_vec3_scale(c01, invdeterminant);
    c23 = mx_vec3_scale(c23, invdeterminant);
    b10 = mx_vec3_scale(b10, invdeterminant);
    b32 = mx_vec3_scale(b32, invdeterminant);

    mx_mat4 result;
    result.columns[0] =
        mx_v4v(mx_vec3_add(mx_vec3_cross(matrix.columns[1].xyz, b32),
                           mx_vec3_scale(c23, matrix.columns[1].w)),
               -mx_vec3_dot(matrix.columns[1].xyz, c23));
    result.columns[1] =
        mx_v4v(mx_vec3_sub(mx_vec3_cross(b32, matrix.columns[0].xyz),
                           mx_vec3_scale(c23, matrix.columns[0].w)),
               +mx_vec3_dot(matrix.columns[0].xyz, c23));
    result.columns[2] =
        mx_v4v(mx_vec3_add(mx_vec3_cross(matrix.columns[3].xyz, b10),
                           mx_vec3_scale(c01, matrix.columns[3].w)),
               -mx_vec3_dot(matrix.columns[3].xyz, c01));
    result.columns[3] =
        mx_v4v(mx_vec3_sub(mx_vec3_cross(b10, matrix.columns[2].xyz),
                           mx_vec3_scale(c01, matrix.columns[2].w)),
               +mx_vec3_dot(matrix.columns[2].xyz, c01));

    return mx_mat4_transpose(result);
}

#endif // mx_math_mtx_h
