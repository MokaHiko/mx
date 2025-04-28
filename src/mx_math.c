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

real_t mx_clampf(float val, float min, float max) {
    if (val < min) {
        return min;
    }

    if (val > max) {
        return max;
    }

    return val;
}

real_t mx_lerpf(float a, float b, float t) { return a * (1 - t) + b * t; }

MX_API void mx_vec3_norm(const mx_vec3 a, mx_vec3 out) {
    real_t len2 = mx_vec3_len_2(a);
    MX_ASSERT(len2 > 0.0, "Cannot normalize vector with length 0.0");

    real_t len = sqrt(len2);
    out[0] = a[0] / len;
    out[1] = a[1] / len;
    out[2] = a[2] / len;
}

real_t mx_vec3_dot(const mx_vec3 a, const mx_vec3 b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }

real_t mx_vec3_len_2(const mx_vec3 a) { return mx_vec3_dot(a, a); }
real_t mx_vec3_len(const mx_vec3 a) { return sqrt(mx_vec3_len_2(a)); }

void mx_vec3_cross(const mx_vec3 a, const mx_vec3 b, mx_vec3 out) {
    out[0] = (a[1] * b[2]) - (a[2] * b[1]);
    out[1] = (a[2] * b[0]) - (a[0] * b[0]);
    out[2] = (a[0] * b[1]) - (a[1] * b[0]);
}

void mx_vec3_scale(const mx_vec3 a, float s, mx_vec3 out) {
    out[0] = a[0] * s;
    out[1] = a[1] * s;
    out[2] = a[2] * s;
}

void mx_vec3_add(const mx_vec3 a, const mx_vec3 b, mx_vec3 out) {
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}

void mx_vec3_sub(const mx_vec3 a, const mx_vec3 b, mx_vec3 out) {
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

void mx_vec3_sub_into(mx_vec3 a, const mx_vec3 b) {
    a[0] = a[0] - b[0];
    a[1] = a[1] - b[1];
    a[2] = a[2] - b[2];
}

void mx_vec3_mul(const mx_vec3 a, const mx_vec3 b, mx_vec3 out) {
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
}


void mx_ivec3_scale(const mx_ivec3 a, int s, mx_ivec3 out) {
    out[0] = a[0] * s;
    out[1] = a[1] * s;
    out[2] = a[2] * s;
}

void mx_ivec3_add(const mx_ivec3 a, const mx_ivec3 b, mx_ivec3 out) {
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}

void mx_ivec3_sub(const mx_ivec3 a, const mx_ivec3 b, mx_ivec3 out) {
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

void mx_ivec3_sub_into(mx_ivec3 a, const mx_ivec3 b) {
    a[0] = a[0] - b[0];
    a[1] = a[1] - b[1];
    a[2] = a[2] - b[2];
}

void mx_ivec3_mul(const mx_ivec3 a, const mx_ivec3 b, mx_ivec3 out) {
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
}
