#ifndef MX_MATH_TYPES_H_
#define MX_MATH_TYPES_H_

#define MX_SIMD

#ifndef MX_DOUBLE_PRECISION
typedef float real_t;
#else
typedef double real_t;
#endif

/**
 * @brief Represents a 2D vector with three real_t components.
 *
 * This vector is used for cartesian coordinates, directions, and other 2D vector calculations.
 */
typedef real_t mx_vec2[2];
#define MX_VEC2_ZERO {0.0f, 0.0f}

/**
 * @brief Represents a 3D vector with three real_t components.
 *
 * This vector is used for spatial coordinates, directions, and other 3D vector calculations.
 */
#ifndef MX_SIMD
typedef real_t mx_vec3[3];
#define MX_VEC3_ZERO (mx_vec3){0.0f, 0.0f, 0.0f}
#else
typedef real_t mx_vec3[4];
#define MX_VEC3_ZERO {0.0f, 0.0f, 0.0f, 0.0f}
#endif

/**
 * @brief Represents a 4D vector with four real_t components.
 *
 * This vector is typically used for homogeneous coordinates or other 4D vector operations.
 */
typedef real_t mx_vec4[4];
#define MX_VEC4_ZERO (mx_vec4){0.0f, 0.0f, 0.0f, 0.0f}

/**
 * @brief Represents a quaternion with four real_t components.
 *
 * This quaternion is stored in the order (w, x, y, z).
 */
typedef real_t mx_quat[4];
#define MX_QUAT_IDENTITY (mx_vec4){1.0f, 0.0f, 0.0f, 0.0f}

#endif
