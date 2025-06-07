#include <mx/mx_memory.h>

#include <assert.h>
#include <stdlib.h>

#include <string.h>

static void* platform_alloc(void* _, size_t size) {
    void* out = malloc(size);
    memset(out, 0, size);
    return out;
}

static void* platform_realloc(void* _, void* ptr, size_t size) {
    return realloc(ptr, size);
}

static void platform_free(void* _, void* ptr) { free(ptr); }

mx_allocator_t mx_default_allocator() {
    return (mx_allocator_t){
        .alloc = platform_alloc,
        .realloc = platform_realloc,
        .free = platform_free,
    };
};

mx_allocator_t mx_allocator_create(mx_buffer* arena) {
    return (mx_allocator_t){
        .alloc = mx_linear_allocate,
        .free = NULL,
        .user_data = arena,
    };
};

mx_allocator_t mx_arena_create(size_t size) {
    mx_buffer* arena = platform_alloc(NULL, sizeof(mx_buffer) + size);

    *arena = (mx_buffer){
        .head = 0,
        .len = size,
        .data = (uint8_t*)arena + sizeof(mx_buffer),
    };

    mx_allocator_t out = {
        .user_data = arena,
        .alloc = mx_linear_allocate,

        .realloc = NULL,
        .free = NULL,
    };

    return out;
}

void mx_arena_destroy(mx_allocator_t arena_allocator) {
    platform_free(NULL, arena_allocator.user_data);
};

void mx_arena_free(mx_buffer* arena) {
    assert(arena->len > 0 && "[Mx]: Arena freed with size 0!");

    arena->head = 0;
    arena->len = 0;

    free(arena->data);
    arena->data = NULL;
}
