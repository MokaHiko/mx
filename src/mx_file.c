#include "mx/mx_file.h"
#include <stdio.h>
#include <string.h>

int mx_read_file(const char* path, size_t* size, void* buffer) {
    FILE* fptr;
    fptr = fopen(path, "rb");

    if (fptr == NULL) {
        return -1;
    }

    fseek(fptr, 0, SEEK_END);
    *size = ftell(fptr);

    if (buffer == NULL) {
        fclose(fptr);
        return MX_SUCCESS;
    }

    rewind(fptr);
    fread(buffer, 1, *size, fptr);

    fclose(fptr);
    return MX_SUCCESS;
}

typedef struct mx_string_slice {
    const char* string;
    uint32_t offset;
    uint32_t length;
} mx_string_slice;

void get_directory(const char* path, mx_string_slice* dir) {
    const size_t path_length = strlen(path);
    const char* file_name = strrchr(path, '/');

    dir->string = path;
    dir->length = file_name - path;
    dir->offset = 0;
}

void get_file(const char* path, mx_string_slice* file) {
    mx_string_slice dir;
    get_directory(path, &dir);

    file->string = path;
    file->length = strlen(path) - dir.length;
    file->offset = dir.length;
}
