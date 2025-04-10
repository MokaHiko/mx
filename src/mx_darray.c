#include "mx/mx_darray.h"
#include "mx/mx_asserts.h"

#include <stdlib.h>
#include <string.h>

typedef struct mx_darray_info {
    size_t head;
    size_t element_size;
    size_t capacity;
} mx_darray_info;

void* mx_darray_create(size_t element_size, mx_allocator* allocator) {
    if (allocator != NULL) {
    }

    mx_darray_info* darray_info = mx_alloc(sizeof(mx_darray_info), 0);
    *darray_info = (mx_darray_info){.head = 0, .element_size = element_size, .capacity = 0};

    return (uint8_t*)darray_info + sizeof(mx_darray_info);
};

size_t mx_darray_count(const mx_darray* items) {
    struct mx_darray_info* info = (mx_darray_info*)((uint8_t*)(*items) - sizeof(mx_darray_info));
    return info->head / info->element_size;
}

void mx_darray_add(mx_darray* darray_ptr, const void* data) {
    MX_ASSERT(darray_ptr != NULL);
    MX_ASSERT((mx_darray_info*)((uint8_t*)(*darray_ptr) - sizeof(mx_darray_info)) != NULL);
    mx_darray_info* info = (mx_darray_info*)((uint8_t*)(*darray_ptr) - sizeof(mx_darray_info));

    size_t new_head = info->head + info->element_size;
    if (new_head > info->capacity) {
        size_t new_capacity = info->capacity > 0 ? info->capacity * 2 : info->element_size;

        info = mx_realloc(info, sizeof(mx_darray_info) + new_capacity);
        info->capacity = new_capacity;
    }

    if (data != NULL) {
        mx_darray darray = (uint8_t*)info + sizeof(mx_darray_info);
        memcpy((uint8_t*)darray + info->head, data, info->element_size);
    } else {
        mx_darray darray = (uint8_t*)info + sizeof(mx_darray_info);
        memset((uint8_t*)darray + info->head, 0, info->element_size);
    }

    info->head = new_head;
    *darray_ptr = (uint8_t*)info + sizeof(mx_darray_info);
}

void mx_darray_destroy(mx_darray* darray_ptr, mx_allocator* allocator) {
    MX_ASSERT(darray_ptr != NULL);
    MX_ASSERT((mx_darray_info*)((uint8_t*)(*darray_ptr) - sizeof(mx_darray_info)) != NULL);
    mx_darray_info* info = (mx_darray_info*)((uint8_t*)(*darray_ptr) - sizeof(mx_darray_info));

    MX_ASSERT(info->capacity > 0);

    info->head = 0;
    info->capacity = 0;
    mx_free(info);
};
