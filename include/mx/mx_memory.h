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
    void* (*alloc)(void* user_ptr, size_t size);
    void* (*realloc)(void* user_ptr, void* ptr, size_t size);
    void (*free)(void* user_ptr, void* ptr);
    void* user_data;
} mx_allocator_t;

#define mx_alloc(allocator, len)        allocator.alloc(allocator.user_data, len)
#define mx_realloc(allocator, ptr, len) allocator.realloc(allocator.user_data, ptr, len)
#define mx_free(allocator, ptr)         allocator.free(allocator.user_data, ptr)

#ifdef __cplusplus
extern "C" {
#endif

// @brief default arena allocator
MX_API inline static void* mx_arena_allocate(void* user_data, size_t len) {
    //assert(len > 0 && "[Mx]: Arena push with size 0!");
    mx_arena* arena = (mx_arena*)user_data;

#ifdef MX_DEBUG
    if (arena->head + len > arena->len) {
        //MX_LOG_ERROR("Arena requested %zu but has remaining %zu\n", len, arena->len - arena->head);
    }
#endif

    //assert(arena->head + len <= arena->len && "[Mx]: Arena push overflow!");
    void* alloc = arena->data + arena->head;
    arena->head += len;

    return alloc;
};


// @brief Returns an allocator using malloc and free
MX_API MX_NO_DISCARD mx_allocator_t mx_default_allocator();
#define MX_DEFAULT_ALLOCATOR mx_default_allocator()

// @brief created a single threaded default allocator
MX_API MX_NO_DISCARD mx_allocator_t mx_allocator_create(mx_arena* arena);

#define mx_scoped_allocator(bytes)                                                                 \
    uint8_t __mx_scoped_temp_buffer[(bytes)];                                                      \
    mx_arena __mx_temp_arena = {.data = __mx_scoped_temp_buffer, .len = bytes};                    \
    mx_allocator_t

#define mx_scoped_allocator_create()                                                               \
    (mx_allocator_t) { .alloc = &mx_arena_allocate, .user_data = &__mx_temp_arena }

#ifdef __cplusplus
}
#endif

#endif
