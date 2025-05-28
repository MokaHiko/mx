#include "mx/mx_string.h"
#include "mx/mx_asserts.h"
#include "mx/mx_log.h"
#include "mx/mx_memory.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

size_t mx_strlen(mx_str string) {
    if (string.len == MX_STR_WHOLE_SIZE) {
        string.len = strlen(string.data) + 1;
    }

    return string.len;
}

mx_str mx_str_allocate(size_t len, mx_allocator_t allocator) {
    MX_ASSERT(len > 0, "Cannot create 0 length string.");

    mx_str str_buff = {.len = len};
    str_buff.data = mx_alloc(allocator, str_buff.len);

    return str_buff;
};

mx_str mx_str_create(const char* str, mx_allocator_t allocator) {
    MX_ASSERT(strlen(str) > 0, "Cannot create 0 length string.");
    MX_ASSERT(str[strlen(str)] == '\0', "Passing non null terminated string!");

    mx_str str_buff = mx_str_allocate(strlen(str) + 1, allocator);
    memcpy(str_buff.data, str, str_buff.len);

    return str_buff;
};

void mx_str_destroy(mx_str string, mx_allocator_t allocator) {
    if (string.data != NULL) {
        mx_free(allocator, string.data);
    };
};

mx_strv mx_strv_create(const char* str) {
    MX_ASSERT(strlen(str) > 0, "Cannot create 0 length string view.");
    MX_ASSERT(str[strlen(str)] == '\0', "Passing non null terminated string view!");

    return (mx_strv){
        .c_str = str,
        .len = strlen(str) + 1,
    };
};

mx_str mx_fmt(mx_allocator_t allocator, mx_strv fmt, ...) {
    va_list args;
    va_start(args, fmt);

    // Get required length
    int length = vsnprintf(NULL, 0, fmt.c_str, args);
    va_end(args);

    if (length < 0)
        return (mx_str){0};

    // Allocate buffer
    mx_str str_buff = mx_str_allocate(length + 1, allocator);

    va_start(args, fmt);
    vsnprintf((char*)str_buff.data, length + 1, fmt.c_str, args);
    va_end(args);

    return str_buff;
}

mx_str mx_strcat(mx_str left, mx_str right, mx_allocator_t allocator) {
    left.len = mx_strlen(left);
    right.len = mx_strlen(right);

    if (left.len <= 0) {
        MX_LOG_WARN("Attempting to concatonate with left empty string");
        return left;
    };

    mx_str str_buff = mx_str_allocate(left.len + right.len - 1, allocator);

    memcpy(str_buff.data, left.data, left.len - 1);
    memcpy(str_buff.data + left.len - 1, right.data, right.len);

    return str_buff;
};

mx_str mx_strcopy(mx_str string, mx_allocator_t allocator) {
    string.len = mx_strlen(string);

    mx_str str_buff = mx_str_allocate(string.len, allocator);
    memcpy(str_buff.data, string.data, string.len);

    return str_buff;
};
