#ifndef MX_DARRAY_H_
#define MX_DARRAY_H_

#include "mx/mx_memory.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MX_DARRAY_GROWTH_FACTOR 2

typedef void* mx_darray;
#define mx_darray_t(element_t) element_t*

MX_API MX_NO_DISCARD void* mx_darray_create(size_t element_size, mx_allocator_t allocator);

MX_API MX_NO_DISCARD size_t mx_darray_count(const mx_darray* items);
MX_API void* mx_darray_push_impl(mx_darray* items, size_t component_size, void* data);

MX_API void mx_darray_add(mx_darray* items, const void* data);
MX_API void mx_darray_remove_at(mx_darray* darray_ptr, uint32_t idx);

MX_API void mx_darray_destroy(mx_darray* darray_ptr, mx_allocator_t allocator);

#define MX_DARRAY_CREATE(element_t, allocator)                                                     \
    ((element_t*)mx_darray_create(sizeof(element_t), allocator))
#define MX_DARRAY_COUNT(darray_ptr) mx_darray_count((void*)darray_ptr)

#define mx_darray_push(darray_ptr, component, ...)                                                 \
    (component*)mx_darray_push_impl((void*)darray_ptr, sizeof(component), &(component)__VA_ARGS__)

#define MX_DARRAY_PUSH(darray_ptr, args)       mx_darray_add((void*)darray_ptr, (element_ptr){args})
#define MX_DARRAY_ADD(darray_ptr, element_ptr) mx_darray_add((void*)darray_ptr, element_ptr)
#define MX_DARRAY_REMOVE_AT(darray_ptr, idx)   mx_darray_remove_at((void*)darray_ptr, idx)

#define MX_DARRAY_DESTROY(darray_ptr, allocator) (mx_darray_destroy((void**)darray_ptr, allocator))

#ifdef __cplusplus
}
#endif

#endif
