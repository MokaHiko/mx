#ifndef MX_STRING_H_
#define MX_STRING_H_

#include "mx/mx.h"

typedef const char* mx_string;

typedef struct MX_API mx_slice {
    mx_string string;
    size_t start;
    size_t size;
} mx_slice;

void mx_string_concat(mx_string a, mx_string b);

#endif
