#ifndef MX_MEMORY_H_
#define MX_MEMORY_H_

#include "mx.h"

#define MX_GB (1024 * 1024 * 1024)
#define MX_MB (1024 * 1024)
#define MX_KB (1024)

/*@brief stack based memory arena.*/
typedef struct MX_API mx_arena {
	uint8_t* data;
	size_t length;
	size_t head;
} mx_arena;

MX_API mx_arena mx_arena_alloc(size_t size);
MX_API void* mx_arena_push(mx_arena* arena, size_t size);
MX_API void mx_arena_reset(mx_arena* arena);
MX_API void mx_arena_free(mx_arena* arena);

#endif
