#ifndef MX_MEMORY_H_
#define MX_MEMORY_H_

#include "mx.h"

#define MX_GB (1024 * 1024 * 1024)
#define MX_MB (1024 * 1024)
#define MX_KB (1024)

typedef enum mx_memory_alloc_flag { MX_MEMORY_ALLOC_FLAG_COUNT } mx_memory_alloc_flag;

typedef struct MX_API mx_arena {
    uint8_t* data;
    size_t len;
    size_t head;
} mx_arena;

typedef struct MX_API mx_allocator_t {
    void* (*alloc)(size_t size);
    void (*free)(void* ptr);
    void* user_data;
} mx_allocator_t;

// @brief created a single threaded default allocator
MX_API MX_NO_DISCARD mx_allocator_t mx_make_allocator(mx_arena arena);
MX_API void mx_allocator_reset(mx_allocator_t arena);
MX_API void mx_free_allocator(mx_allocator_t allocator);

MX_API void* mx_alloc(size_t len, mx_memory_alloc_flag flags);

MX_API void* mx_realloc(void* data, size_t len);

MX_API void mx_free(void* data);

MX_API mx_arena mx_arena_alloc(size_t size);
MX_API MX_NO_DISCARD void* mx_arena_push(mx_arena* arena, size_t size);
MX_API void mx_arena_reset(mx_arena* arena);
MX_API void mx_arena_free(mx_arena* arena);

#endif
