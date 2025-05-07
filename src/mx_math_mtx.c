#include "mx/mx_math_mtx.h"

#include <string.h>


inline mx_mat4 mx_mat4_identity(void) { return _mat4_diagonal(1.0f); };

void mx_mat4_inverse(const mx_mat4 a, const mx_mat4 b, mx_mat4 out) {}

mx_mat4 mx_mat4_transpose(mx_mat4 matrix) {
    mx_mat4 result;

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

    return result;
}

