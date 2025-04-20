#include "mx/mx_math_mtx.h"

#include "mx/mx_math.h"
#include <string.h>

void mx_mat4_mul(const mx_mat4 a, const mx_mat4 b, mx_mat4 out) {
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            out[col * 4 + row] = a[0 * 4 + row] * b[col * 4 + 0] + a[1 * 4 + row] * b[col * 4 + 1] +
                                 a[2 * 4 + row] * b[col * 4 + 2] + a[3 * 4 + row] * b[col * 4 + 3];
        }
    }
}

void mx_mat4_inverse(const mx_mat4 a, const mx_mat4 b, mx_mat4 out) {}

void mx_mat4_transpose(const mx_mat4 matrix, mx_mat4 out) {
    out[0] = matrix[0];
    out[1] = matrix[4];
    out[2] = matrix[8];
    out[3] = matrix[12];
    out[4] = matrix[1];
    out[5] = matrix[5];
    out[6] = matrix[9];
    out[7] = matrix[13];
    out[8] = matrix[2];
    out[9] = matrix[6];
    out[10] = matrix[10];
    out[11] = matrix[14];
    out[12] = matrix[3];
    out[13] = matrix[7];
    out[14] = matrix[11];
    out[15] = matrix[15];
}

/*|  2/(r-l)     0         0        -(r+l)/(r-l) |*/
/*|    0      2/(t-b)      0        -(t+b)/(t-b) |*/
/*|    0         0     -2/(f-n)     -(f+n)/(f-n) |*/
/*|    0         0         0             1       |*/
void mx_ortho(real_t left, real_t right, real_t bottom, real_t top, real_t near, real_t far, mx_mat4 out) {
    memset(out, 0, sizeof(mx_mat4));

    real_t rl = 1.0f / (right - left);
    real_t tb = 1.0f / (top - bottom);
    real_t fn = 1.0f / (far - near);

    out[0] = 2.0f * rl;
    out[5] = 2.0f * tb;
    out[10] = -2.0f * fn;
    out[15] = 1.0f;

    out[12] = -(right + left) * rl;
    out[13] = -(top + bottom) * tb;
    out[14] = -(far + near) * fn;
}

void mx_perspective(real_t fov_radians, real_t aspect_ratio, real_t near, real_t far, mx_mat4 out) {
    real_t half_tan_fov = mx_tan(fov_radians * 0.5f);

    out[0] = 1.0f / (aspect_ratio * half_tan_fov);
    out[5] = 1.0f / half_tan_fov;
    out[10] = -((far + near) / (far - near));
    out[15] = 1.0f;

    out[11] = -1.0f;
    out[14] = -((2.0f * far * near) / (far - near));
}

void mx_translate(const mx_vec3 position, mx_mat4 out) {
    out[12] += position[0];
    out[13] += position[1];
    out[14] += position[2];
}

void mx_scale(const mx_vec3 scale, mx_mat4 out) {
    out[0] *= scale[0];
    out[5] *= scale[1];
    out[10] *= scale[2];
}

static void mx_rotate_euler_x(real_t angle, mx_mat4 out) {
    real_t c = mx_cos(angle);
    real_t s = mx_sin(angle);

    out[5] = c;
    out[6] = s;
    out[9] = -s;
    out[10] = c;
}

static void mx_rotate_euler_y(real_t angle, mx_mat4 out) {
    real_t c = mx_cos(angle);
    real_t s = mx_sin(angle);

    out[0] = c;
    out[2] = -s;
    out[8] = s;
    out[10] = c;
}

static void mx_rotate_euler_z(real_t angle, mx_mat4 out) {
    real_t c = mx_cos(angle);
    real_t s = mx_sin(angle);

    out[0] = c;
    out[1] = s;
    out[4] = -s;
    out[5] = c;
}

void mx_mat4_rotate_euler(const mx_vec3 euler, mx_mat4 out) {
    mx_mat4 rx = MX_MAT4_IDENTITY;
    mx_mat4 ry = MX_MAT4_IDENTITY;
    mx_mat4 rz = MX_MAT4_IDENTITY;

    mx_rotate_euler_x(euler[0], rx);
    mx_rotate_euler_y(euler[1], ry);
    mx_rotate_euler_z(euler[2], rz);

    // rz * ry * rx * out
    mx_mat4 temp = MX_MAT4_IDENTITY;
    mx_mat4_mul(ry, rz, temp);  // out = ry * rx;
    mx_mat4_mul(rx, temp, out); // out = rz * out
}
