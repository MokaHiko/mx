#ifndef MX_MATH_MTX_H_
#define MX_MATH_MTX_H_

#include "mx.h"
#include "mx_math_types.h"

typedef real_t mx_mat4[16];
#define MX_MAT4_IDENTITY {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}

MX_API void mx_perspective(real_t fov, real_t aspect_ratio, real_t near, real_t far, mx_mat4 out);

MX_API void mx_translate(const mx_vec3 position, mx_mat4 out_matrix);

#endif
