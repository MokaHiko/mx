#ifndef MX_MATH_MTX_H_
#define MX_MATH_MTX_H_

#include "mx.h"
#include "mx_math_types.h"

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
typedef real_t mx_mat4[16];

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
#define MX_MAT4_IDENTITY {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}

/**
 * @brief Multiplies two 4x4 matrices.
 *
 * This function multiplies two 4x4 matrices `a` and `b` and stores the result in `out`.
 * The mathematical form of the matrix multiplication is:
 *
 * out = a * b
 *
 * Where `a` and `b` are 4x4 matrices, and the resulting `out` matrix is calculated by:
 *
 * out[row, col] = a[row, 0] * b[0, col] + a[row, 1] * b[1, col] + a[row, 2] * b[2, col] + a[row, 3] * b[3,
 * col]
 *
 * @note If `out` is the same as either `a` or `b`, the result is undefined as the matrices are overwritten
 * during the operation.
 *
 * @param a The first matrix.
 * @param b The second matrix.
 * @param out The result of the multiplication. This cannot be the same as `a` or `b`.
 */
MX_API void mx_mat4_mul(const mx_mat4 a, const mx_mat4 b, mx_mat4 out);

// Main macro that handles multiple matrix arguments.
#define MX_MAT4_MUL(result, ...) mx_mat4_mul_multiple_helper(result, __VA_ARGS__)

/**
 * @brief Creates an orthogonal projection matrix.
 *
 * This function generates an orthographic projection matrix, which is used for orthogonal projection.
 * The mathematical form of the matrix is:
 *
 * out =
 * |  2/(r-l)   0           0           -(r+l)/(r-l) |
 * |  0          2/(t-b)    0           -(t+b)/(t-b) |
 * |  0          0          -2/(f-n)     -(f+n)/(f-n) |
 * |  0          0           0           1           |
 *
 * Where:
 * - `l` is the left clipping plane.
 * - `r` is the right clipping plane.
 * - `b` is the bottom clipping plane.
 * - `t` is the top clipping plane.
 * - `n` is the near clipping plane.
 * - `f` is the far clipping plane.
 *
 * @param l The left clipping plane.
 * @param r The right clipping plane.
 * @param b The bottom clipping plane.
 * @param t The top clipping plane.
 * @param n The near clipping plane.
 * @param f The far clipping plane.
 * @param out The resulting orthographic projection matrix.
 */
MX_API void mx_ortho(real_t l, real_t r, real_t b, real_t t, real_t n, real_t f, mx_mat4 out);

/**
 * @brief Creates a perspective projection matrix.
 *
 * This function creates a perspective projection matrix used for perspective projection in 3D space.
 * The mathematical form of the matrix is:
 *
 * out =
 * | 1/(tan(fov/2) * aspect)   0           0                       0           |
 * | 0                         1/tan(fov/2) 0                       0           |
 * | 0                         0           (f+near)/(f-near)       -2*f*near/(f-near) |
 * | 0                         0           1                       0           |
 *
 * Where:
 * - `fov` is the field of view.
 * - `aspect` is the aspect ratio of the screen or view.
 * - `near` is the near clipping plane.
 * - `far` is the far clipping plane.
 *
 * @param fov The field of view (in radians).
 * @param aspect_ratio The aspect ratio of the screen.
 * @param near The near clipping plane.
 * @param far The far clipping plane.
 * @param out The resulting perspective projection matrix.
 */
MX_API void mx_perspective(real_t fov, real_t aspect_ratio, real_t near, real_t far, mx_mat4 out);

/**
 * @brief Translates a matrix by a position vector.
 *
 * This function translates (moves) the matrix by the specified position vector. Mathematically, this is
 * represented as:
 *
 * out =
 * | 1    0    0    x |
 * | 0    1    0    y |
 * | 0    0    1    z |
 * | 0    0    0    1 |
 *
 * Where `x`, `y`, and `z` are the components of the position vector and `out` is the original matrix.
 *
 * @param position The translation vector (a 3D vector).
 * @param out The matrix to be translated.
 */
MX_API void mx_translate(const mx_vec3 position, mx_mat4 out);

/**
 * @brief Scales a matrix by a scale vector.
 *
 * This function scales the matrix by the provided scale vector. Mathematically, this is represented as:
 *
 * out =
 * | sx   0    0    0 |
 * | 0    sy   0    0 |
 * | 0    0    sz   0 |
 * | 0    0    0    1 |
 *
 * Where `sx`, `sy`, and `sz` are the scale components for the X, Y, and Z axes respectively, and `out` is the
 * matrix to be scaled.
 *
 * @param scale The scale vector (a 3D vector).
 * @param out The matrix to be scaled.
 */
MX_API void mx_scale(const mx_vec3 scale, mx_mat4 out);

/**
 * @brief Creates a rotation matrix by Euler angles.
 *
 * This function creates a rotation matrix from the specified Euler angles in XYZ order. Mathematically, the
 * rotation matrix is composed of individual rotation matrices around each axis. The result is:
 *
 * out = Rz(angle_z) * Ry(angle_y) * Rx(angle_x)
 *
 * Where:
 * - Rx(angle_x) is the rotation matrix around the X-axis.
 * - Ry(angle_y) is the rotation matrix around the Y-axis.
 * - Rz(angle_z) is the rotation matrix around the Z-axis.
 *
 * The individual rotation matrices are:
 *
 * Rotation around X-axis:
 * Rx =
 * | 1   0          0           0 |
 * | 0   cos(angle_x)  -sin(angle_x)  0 |
 * | 0   sin(angle_x)   cos(angle_x)   0 |
 * | 0   0          0           1 |
 *
 * Rotation around Y-axis:
 * Ry =
 * | cos(angle_y)   0   sin(angle_y)   0 |
 * | 0              1   0              0 |
 * | -sin(angle_y)  0   cos(angle_y)   0 |
 * | 0              0   0              1 |
 *
 * Rotation around Z-axis:
 * Rz =
 * | cos(angle_z)   -sin(angle_z)  0   0 |
 * | sin(angle_z)   cos(angle_z)   0   0 |
 * | 0              0              1   0 |
 * | 0              0              0   1 |
 *
 * @param euler The Euler angles (in radians) for the rotation around X, Y, and Z axes.
 * @param out The resulting rotation matrix.
 */
MX_API void mx_mat4_rotate_euler(const mx_vec3 euler, mx_mat4 out);

#endif
