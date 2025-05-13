#ifndef MX_STRING_H_
#define MX_STRING_H_

#include "mx/mx.h"
#include "mx/mx_memory.h"

enum { MX_STRV_WHOLE_SIZE = 0 };

typedef struct MX_API mx_str {
    uint8_t* data;
    size_t len;
    size_t capacity;
    mx_allocator_t allocator;
} mx_str;

MX_API MX_NO_DISCARD mx_str mx_str_create(const char* str, mx_allocator_t allocator);

typedef struct MX_API mx_strv {
    const char* c_str;
    size_t len; // If 0 then assumed entire length
} mx_strv;

MX_API MX_NO_DISCARD mx_strv mx_strv_create(const char* str);

#endif
