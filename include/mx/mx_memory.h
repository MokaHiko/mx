#ifndef MX_MEMORY_H_
#define MX_MEMORY_H_

#include "mx.h"

#define MX_GB (1024 * 1024 * 1024)
#define MX_MB (1024 * 1024)
#define MX_KB (1024)

// @brief API stack based memory arena.
typedef struct MX_API {
	uint8_t* data;
	size_t length;
	size_t head;
} MxArena;

MX_API MxArena mx_arena_alloc(size_t size);
MX_API void* mx_arena_push(MxArena* arena, size_t size);
MX_API void mx_arena_reset(MxArena* arena);
MX_API void mx_arena_free(MxArena* arena);

#endif
