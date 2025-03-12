#ifndef MX_FILE_H_
#define MX_FILE_H_

#include "mx/mx.h"
#include "mx/mx_string.h"

typedef struct MX_API mx_path {
    const mx_string path;
} mx_path;

/*@returns MX_SUCCESS if file exists.*/
MX_API int mx_read_file(const char* path, size_t* size, void* buffer);

#endif
