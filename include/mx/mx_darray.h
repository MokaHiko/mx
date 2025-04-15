#ifndef MX_DARRAY_H_
#define MX_DARRAY_H_

#include "mx/mx_memory.h"

#define MX_DARRAY_GROWTH_FACTOR 2

typedef void* mx_darray;

MX_API MX_NO_DISCARD void* mx_darray_create(size_t element_size, mx_allocator* allocator);

MX_API MX_NO_DISCARD size_t mx_darray_count(const mx_darray* items);

MX_API void mx_darray_add(mx_darray* items, const void* data);

MX_API void mx_darray_destroy(mx_darray* darray_ptr, mx_allocator* allocator);

#define MX_DARRAY_CREATE(element_t, allocator) ((element_t*)mx_darray_create(sizeof(element_t), allocator))
#define MX_DARRAY_COUNT(darray_ptr) mx_darray_count((void*)darray_ptr)

// TODO: Accept struct params
#define MX_DARRAY_ADD(darray_ptr, element_ptr) mx_darray_add((void*)darray_ptr, element_ptr)

#endif
