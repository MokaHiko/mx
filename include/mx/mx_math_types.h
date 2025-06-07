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
 * This vector is used for cartesian coordinates, directions, and other 2D vector
 * calculations.
 */
typedef real_t mx_vec2[2];
#define MX_VEC2_ZERO {0.0f, 0.0f}

/**
 * @brief Represents a 3D vector with three real_t components.
 *
 * This vector is used for spatial coordinates, directions, and other 3D vector
 * calculations.
 */
#ifndef MX_SIMD
typedef real_t mx_vec3[3];
#define MX_VEC3_ZERO (mx_vec3){0.0f, 0.0f, 0.0f}
#else
typedef union mx_vec3 {
    real_t elements[3];

    struct {
        real_t x, y, z;
    };

    struct {
        real_t r, g, b;
    };

    struct {
        real_t xy;
        real_t _ignored;
    };
} mx_vec3;

#define MX_VEC3_ZERO  (mx_vec3){0.0, 0.0, 0.0}
#define MX_VEC3_ONE   (mx_vec3){1.0, 1.0, 1.0}
#define MX_VEC3_UP    (mx_vec3){0.0, 1.0, 0.0}
#define MX_VEC3_RIGHT (mx_vec3){1.0, 0.0, 0.0}

#endif

/**
 * @brief Represents a 4D vector with four real_t components.
 *
 * This vector is typically used for homogeneous coordinates or other 4D vector
 * operations.
 */
typedef union mx_vec4 {
    real_t elements[4];

    struct {
        real_t x, y, z, w;
    };

    struct {
        real_t r, g, b, a;
    };

    struct {
        mx_vec3 xyz;
        real_t _ignored;
    };
} mx_vec4;
#define MX_VEC4_ZERO (mx_vec4){0.0f, 0.0f, 0.0f, 0.0f}

/**
 * @brief Represents a 2D vector with three signed 32 bit int components.
 *
 */
#ifndef MX_SIMD
typedef real_t mx_ivec2[2];
#define MX_IVEC3_ZERO (mx_vec3){0, 0, 0}
#else
typedef union mx_ivec2 {
    int elements[2];

    struct {
        int x, y;
    };

} mx_ivec2;
#define MX_IVEC3_ZERO {0, 0, 0, 0}
#endif

/**
 * @brief Represents a 3D vector with three signed 32 bit int components.
 *
 * This vector is used for spatial coordinates, directions, and other 3D vector
 * calculations.
 */
#ifndef MX_SIMD
typedef real_t mx_ivec3[3];
#define MX_IVEC3_ZERO (mx_vec3){0, 0, 0}
#else
typedef union mx_ivec3 {
    int elements[4];

    struct {
        int x, y, z;
    };

    struct {
        int xy;
        int _ignored;
    };
} mx_ivec3;
#define MX_IVEC3_ZERO {0, 0, 0, 0}
#endif

typedef union mx_quat {
    float elements[4];

    struct {
        union {
            mx_vec3 xyz;
            struct {
                float x, y, z;
            };
        };

        float w;
    };
} mx_quat;
#define MX_QUAT_IDENTITY (mx_quat){0, 0, 0, 1}

#endif
