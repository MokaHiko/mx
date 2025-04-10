#ifndef MX_HASH_H_
#define MX_HASH_H_

#include "mx/mx.h"
#include "mx/mx_darray.h"

#include <uthash/uthash.h>

MX_API void mx_murmur_hash_32(const void* key, int len, uint32_t seed, uint32_t* out);

#define MX_UNORDERED_MAP(name, key_t, value_t)                                                               \
    typedef struct name##_entry {                                                                            \
        key_t key;                                                                                           \
        value_t value;                                                                                       \
        UT_hash_handle hh;                                                                                   \
    } name##_entry;                                                                                          \
    typedef struct name {                                                                                    \
        name##_entry* entries;                                                                               \
        name##_entry* entry_darray;                                                                          \
    } name;                                                                                                  \
    static inline void name##_insert(struct name* map, const key_t* key, const value_t* value) {             \
        name##_entry item = {.key = *key, .value = *value};                                                  \
        mx_darray_add(map->entry_darray, &item);                                                             \
        HASH_ADD(hh, map->entries, key, sizeof(key_t), &item);                                               \
    }                                                                                                        \
    static inline void name##_look_up(struct name* map, const key_t* key, name##_entry* out_entry) {         \
        HASH_FIND(hh, map->entries, key, sizeof(key_t), out_entry);                                          \
    }

#endif
