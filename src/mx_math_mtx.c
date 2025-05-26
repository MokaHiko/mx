#include "mx/mx_math_mtx.h"

#include <string.h>

inline mx_mat4 mx_mat4_identity(void) { return _mat4_diagonal(1.0f); };
