#ifndef MX_STRING_H_
#define MX_STRING_H_

#include "mx/mx.h"
#include "mx/mx_memory.h"

enum { MX_STR_WHOLE_SIZE = 0 };

typedef struct MX_API mx_strv {
    const char* c_str;
    size_t len;
} mx_strv;

typedef struct MX_API mx_str {
    union {
        mx_strv strv;

        struct {
            char* data;
            size_t len;
        };
    };

    size_t capacity;
} mx_str;

#ifdef __cplusplus
extern "C" {
#endif

MX_API MX_NO_DISCARD mx_str mx_str_allocate(size_t len, mx_allocator_t allocator);
MX_API MX_NO_DISCARD mx_str mx_str_create(const char* str, mx_allocator_t allocator);

MX_API void mx_str_destroy(mx_str string, mx_allocator_t allocator);

MX_API MX_NO_DISCARD mx_str mx_strcat(mx_str left, mx_str right, mx_allocator_t allocator);
MX_API MX_NO_DISCARD mx_str mx_strcopy(mx_str string, mx_allocator_t allocator);
MX_API MX_NO_DISCARD mx_str mx_fmt(mx_allocator_t allocator, mx_strv fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
