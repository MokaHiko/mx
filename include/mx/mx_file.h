#ifndef MX_FILE_H
#define MX_FILE_H

#include <mx/mx.h>

// @returns MX_SUCCESS if file exists.
int mx_read_file(const char* path, size_t* size, void* buffer);

#endif
