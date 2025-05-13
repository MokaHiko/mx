#ifndef MX_HASH_H_
#define MX_HASH_H_

#include "mx/mx.h"
#include <uthash/uthash.h>

MX_API void mx_murmur_hash_32(const void* key, int len, uint32_t seed, uint32_t* out);

#define mx_safe_cast(ptr, value_t) = value_t(ptr)

typedef void(*mx_map_add_fn(int));

// Map entry struct generator with unique name
#define mx_map_t(key_t, value_t, elem_count)                                                       \
    typedef struct {                                                                               \
        key_t key;                                                                                 \
        value_t value;                                                                             \
        UT_hash_handle hh;                                                                         \
    } mx_concat(mx_concat(key_t, value_t), _map_entry);                                            \
    typedef struct {                                                                               \
        mx_concat(mx_concat(key_t, value_t), _map_entry) entries[elem_count];                      \
        mx_concat(mx_concat(key_t, value_t), _map_entry) * head;                                   \
        uint32_t entry_count;                                                                      \
    } mx_concat(mx_concat(key_t, value_t), _map);                                                  \
    MX_NO_DISCARD static inline value_t* mx_concat(mx_concat(mx_concat(key_t, value_t), _map),     \
                                                   _find)(                                         \
        mx_concat(mx_concat(key_t, value_t), _map) * mx_map_ptr, key_t key) {                      \
        mx_concat(mx_concat(key_t, value_t), _map_entry) * entry;                                  \
        HASH_FIND(hh, mx_map_ptr->head, &key, sizeof(key), entry);                                 \
        return entry ? &entry->value : NULL;                                                       \
    };                                                                                             \
    static inline void mx_concat(mx_concat(mx_concat(key_t, value_t), _map),                       \
                                 _insert)(mx_concat(mx_concat(key_t, value_t), _map) * mx_map_ptr, \
                                          key_t key,                                               \
                                          const value_t* value_ptr) {                              \
        memcpy(&mx_map_ptr->entries[mx_map_ptr->entry_count].value, value_ptr, sizeof(value_t));   \
        mx_map_ptr->entries[mx_map_ptr->entry_count].key = key;                                    \
        HASH_ADD(hh,                                                                               \
                 mx_map_ptr->head,                                                                 \
                 key,                                                                              \
                 sizeof(key),                                                                      \
                 &mx_map_ptr->entries[mx_map_ptr->entry_count]);                                   \
        ++mx_map_ptr->entry_count;                                                                 \
    };                                                                                             \
    mx_concat(mx_concat(key_t, value_t), _map)

#endif
