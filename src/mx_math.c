#include "mx/mx_math.h"

#include "mx/mx_asserts.h"
#include "mx/mx_math_types.h"

#include <math.h>

real_t mx_sin(real_t radians) {
#ifndef MX_DOUBLE_PRECISION
    return sinf(radians);
#else
    return sin(radians);
#endif
}

real_t mx_cos(real_t radians) {
#ifndef MX_DOUBLE_PRECISION
    return cosf(radians);
#else
    return cos(radians);
#endif
}

real_t mx_tan(real_t radians) {
#ifndef MX_DOUBLE_PRECISION
    return tanf(radians);
#else
    return tan(radians);
#endif
}

real_t mx_pow(real_t base, real_t n) {
#ifndef MX_DOUBLE_PRECISION
    return powf(base, n);
#else
    return pow(base, n);
#endif
}

real_t mx_clamp(real_t val, real_t min, real_t max) {
    if (val < min) {
        return min;
    }

    if (val > max) {
        return max;
    }

    return val;
}

real_t mx_lerpf(float a, float b, float t) { return a * (1 - t) + b * t; }

mx_vec3 mx_vec3_norm(mx_vec3 a) {
    real_t len2 = mx_vec3_len_2(a);
    MX_ASSERT(len2 > 0.0, "Cannot normalize vector with length 0.0");

    real_t len = sqrt(len2);
    return (mx_vec3){a.x / len, a.y / len, a.z / len};
}

real_t mx_vec3_dot(const mx_vec3 a, const mx_vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

real_t mx_vec3_len_2(const mx_vec3 a) { return mx_vec3_dot(a, a); }
real_t mx_vec3_len(const mx_vec3 a) { return sqrt(mx_vec3_len_2(a)); }

mx_vec3 mx_vec3_cross(mx_vec3 a, mx_vec3 b) {
    return (mx_vec3){
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x),
    };
}

mx_vec3 mx_vec3_scale(mx_vec3 a, float s) { return (mx_vec3){a.x * s, a.y * s, a.z * s}; }

mx_vec3 mx_vec3_add(mx_vec3 a, mx_vec3 b) { return (mx_vec3){a.x + b.x, a.y + b.y, a.z + b.z}; }

mx_vec3 mx_vec3_sub(mx_vec3 a, mx_vec3 b) { return (mx_vec3){a.x - b.x, a.y - b.y, a.z - b.z}; }

mx_vec3 mx_vec3_mul(mx_vec3 a, mx_vec3 b) { return (mx_vec3){a.x * b.x, a.y * b.y, a.z * b.z}; }

mx_ivec3 mx_ivec3_scale(mx_ivec3 a, int s) { return (mx_ivec3){a.x * s, a.y * s, a.z * s}; }

mx_ivec3 mx_ivec3_add(mx_ivec3 a, mx_ivec3 b) {
    return (mx_ivec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

mx_ivec3 mx_ivec3_sub(mx_ivec3 a, mx_ivec3 b) {
    return (mx_ivec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

mx_ivec3 mx_ivec3_mul(mx_ivec3 a, mx_ivec3 b) {
    return (mx_ivec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

