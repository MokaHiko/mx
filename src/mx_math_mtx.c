#include "mx/mx_math_mtx.h"

#include "mx/mx_math.h"

void mx_mat4_mul(mx_mat4 a, mx_mat4 b) {}

void mx_mat4_inverse(mx_mat4 a, mx_mat4 b) {}

void mx_ortho(real_t left, real_t right, real_t bottom, real_t top, real_t near, real_t far, mx_mat4 out) {
    real_t rl = 1.0f / (right - left);
    real_t tb = 1.0f / (top - bottom);
    real_t fn = 1.0f / (far - near);

    out[0] = 2.0f * rl;
    out[5] = 2.0f * tb;
    out[10] = -2.0f * fn;
    out[12] = -(right + left) * rl;
    out[13] = -(top + bottom) * tb;
    out[14] = -(far + near) * fn;
}

void mx_perspective(real_t fov_radians, real_t aspect_ratio, real_t near, real_t far, mx_mat4 out) {
    real_t half_tan_fov = mx_tan(fov_radians * 0.5f);

    out[0] = 1.0f / (aspect_ratio * half_tan_fov);
    out[5] = 1.0f / half_tan_fov;
    out[10] = -((far + near) / (far - near));
    out[11] = -1.0f;
    out[14] = -((2.0f * far * near) / (far - near));
}

void mx_translate(const mx_vec3 position, mx_mat4 out) {
    out[12] = position[0];
    out[13] = position[1];
    out[14] = position[2];
}
