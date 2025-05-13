#include <mx/mx_memory.h>

#include "mx/mx_asserts.h"
#include "mx/mx_log.h"

#include <assert.h>
#include <stdlib.h>

mx_allocator_t mx_default_allocator() {
    return (mx_allocator_t){
        .alloc = malloc,
        .free = free,
    };
};

static mx_arena default_allocator;

static void* mx_default_alloc(size_t size) { return mx_arena_push(&default_allocator, size); }

static void mx_default_free(void* data) {}

mx_allocator_t mx_make_allocator(mx_arena arena) {
    MX_ASSERT(default_allocator.data == NULL, "Previous allocator not freed");

    mx_arena_reset(&default_allocator);
    default_allocator = arena;

    mx_arena_reset(&default_allocator);
    return (mx_allocator_t){.alloc = mx_default_alloc, .free = mx_default_free};
};

void mx_allocator_reset(mx_allocator_t allocator) { mx_arena_reset(&default_allocator); }

void mx_free_allocator(mx_allocator_t allocator) { default_allocator = (mx_arena){0}; };

void* mx_alloc(size_t len, mx_memory_alloc_flag flags) { return malloc(len); }
void* mx_realloc(void* data, size_t len) { return realloc(data, len); }
void mx_free(void* data) { free(data); }

mx_arena mx_arena_alloc(size_t size) {
    assert(size > 0 && "[Mx]: Arena created with size 0!");
    return (mx_arena){
        .data = malloc(size),
        .len = size,
        .head = 0,
    };
}

void* mx_arena_push(mx_arena* arena, size_t size) {
    assert(size > 0 && "[Mx]: Arena push with size 0!");

#ifdef MX_DEBUG
    if (arena->head + size > arena->len) {
        MX_LOG_ERROR("Arena requested %zu but has remaining %zu\n", size, arena->len - arena->head);
    }
#endif

    assert(arena->head + size <= arena->len && "[Mx]: Arena push overflow!");
    void* alloc = arena->data + arena->head;
    arena->head += size;

    return alloc;
}

void mx_arena_reset(mx_arena* arena) { arena->head = 0; }

void mx_arena_free(mx_arena* arena) {
    assert(arena->len > 0 && "[Mx]: Arena freed with size 0!");

    arena->head = 0;
    arena->len = 0;

    free(arena->data);
    arena->data = NULL;
}
