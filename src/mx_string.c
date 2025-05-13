#include "mx/mx_string.h"
#include "mx/mx_asserts.h"
#include <string.h>

mx_str mx_str_create(const char* str, mx_allocator_t allocator) {
    MX_ASSERT(strlen(str) > 0, "Cannot create 0 length string.");
    MX_ASSERT(str[strlen(str)] == '\0', "Passing non null terminated string!");

    mx_str str_buff = {
        .allocator = allocator,
        .len = strlen(str) + 1,
    };

    str_buff.data = (uint8_t*)allocator.alloc(str_buff.len);
    memcpy(str_buff.data, str, str_buff.len);

    return str_buff;
};

mx_strv mx_strv_create(const char* str) {
    MX_ASSERT(strlen(str) > 0, "Cannot create 0 length string view.");
    MX_ASSERT(str[strlen(str)] == '\0', "Passing non null terminated string view!");

    return (mx_strv){
        .c_str = str,
        .len = strlen(str) + 1,
    };
};
