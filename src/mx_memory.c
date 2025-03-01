#include <mx/mx_memory.h>

#include "mx/mx_log.h"

#include <stdlib.h>
#include <assert.h>

MxArena mx_arena_alloc(size_t size) {
	assert(size > 0 && "[Mx]: Arena created with size 0!");
	return (MxArena) {
		.data = malloc(size),
		.length = size,
		.head = 0,
	};
}

void* mx_arena_push(MxArena* arena, size_t size) {
	assert(size > 0 && "[Mx]: Arena push with size 0!");

#ifdef MX_DEBUG
	if(arena->head + size >= arena->length) {
		MX_LOG_ERROR("Arena requested %zu but has remaining %zu\n", size, arena->length - arena->head);
	}
#endif

	assert(arena->head + size <= arena->length && "[Mx]: Arena push overflow!");
	void* alloc = arena->data + arena->head;
	arena->head += size;

	return alloc;
}

void mx_arena_reset(MxArena* arena) {
	arena->head = 0;
}

void mx_arena_free(MxArena* arena) {
	assert(arena->length > 0 && "[Mx]: Arena freed with size 0!");

	arena->head = 0;
	arena->length = 0;

	free(arena->data);
	arena->data = NULL;
}
