#ifndef MX_HASH_H_
#define MX_HASH_H_

#include "mx/mx.h"
#include <uthash/uthash.h>

MX_API void mx_murmur_hash_32(const void* key, int len, uint32_t seed, uint32_t* out);

#define mx_map_t(key_t, value_t, elem_count)                                             \
    typedef struct {                                                                     \
        key_t key;                                                                       \
        value_t value;                                                                   \
        UT_hash_handle hh;                                                               \
    } mx_concat(mx_concat(key_t, value_t), _map_entry);                                  \
    typedef struct {                                                                     \
        mx_concat(mx_concat(key_t, value_t), _map_entry) entries[elem_count];            \
        mx_concat(mx_concat(key_t, value_t), _map_entry) * head;                         \
        uint32_t entry_count;                                                            \
    } mx_concat(mx_concat(key_t, value_t), _map);                                        \
    mx_concat(mx_concat(key_t, value_t), _map)

#define mx_map_find_fn(fn_name, key_t, value_t)                                          \
    MX_NO_DISCARD static inline value_t* fn_name(                                        \
        mx_concat(mx_concat(key_t, value_t), _map) * mx_map_ptr,                         \
        key_t key) {                                                                     \
        mx_concat(mx_concat(key_t, value_t), _map_entry) * entry;                        \
        HASH_FIND(hh, mx_map_ptr->head, &key, sizeof(key), entry);                       \
        return entry ? &entry->value : NULL;                                             \
    };

#define mx_map_insert_fn(fn_name, key_t, value_t)                                        \
    static inline void fn_name(mx_concat(mx_concat(key_t, value_t), _map) * mx_map_ptr,  \
                               key_t key,                                                \
                               const value_t* value_ptr) {                               \
        MX_ASSERT(mx_map_ptr->entry_count <                                              \
                  sizeof(mx_map_ptr->entries) /                                          \
                      sizeof(mx_concat(mx_concat(key_t, value_t), _map_entry)));         \
        memcpy(&mx_map_ptr->entries[mx_map_ptr->entry_count].value,                      \
               value_ptr,                                                                \
               sizeof(value_t));                                                         \
        mx_map_ptr->entries[mx_map_ptr->entry_count].key = key;                          \
        HASH_ADD(hh,                                                                     \
                 mx_map_ptr->head,                                                       \
                 key,                                                                    \
                 sizeof(key),                                                            \
                 &mx_map_ptr->entries[mx_map_ptr->entry_count]);                         \
        ++mx_map_ptr->entry_count;                                                       \
    };

#endif
