#include <mx/mx_memory.h>

#include <assert.h>
#include <stdlib.h>

typedef struct memory_profiler {
} memory_profiler;

static void* platform_alloc(void* _, size_t size) { return malloc(size); }

static void* platform_realloc(void* _, void* ptr, size_t size) { return realloc(ptr, size); }

static void platform_free(void* _, void* ptr) { free(ptr); }

mx_allocator_t mx_default_allocator() {
    return (mx_allocator_t){
        .alloc = platform_alloc,
        .realloc = platform_realloc,
        .free = platform_free,
    };
};

mx_allocator_t mx_allocator_create(mx_arena* arena) {
    return (mx_allocator_t){
        .alloc = mx_arena_allocate,
        .free = NULL,
        .user_data = arena,
    };
};

void mx_arena_reset(mx_arena* arena) { arena->head = 0; }

void mx_arena_free(mx_arena* arena) {
    assert(arena->len > 0 && "[Mx]: Arena freed with size 0!");

    arena->head = 0;
    arena->len = 0;

    free(arena->data);
    arena->data = NULL;
}
