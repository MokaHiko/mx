#ifndef MX_ASSERTS_H
#define MX_ASSERTS_H

#include <mx/mx_log.h>

#ifdef MX_DEBUG

#ifdef _MSC_VER
#define MX_ASSERT(cond, ...)                                                   \
    do {                                                                       \
        if (!(cond)) {                                                         \
            MX_LOG_ERROR("Assertion failed: %s", #cond);                       \
            MX_LOG_ERROR("Location: %s:%d", __FILE__, __LINE__);               \
            MX_LOG_ERROR("" __VA_ARGS__);                                      \
            __debugbreak();                                                    \
        }                                                                      \
    } while (0)
#else
#define MX_ASSERT(cond, ...)                                                   \
    do {                                                                       \
        if (!(cond)) {                                                         \
            MX_LOG_ERROR("Assertion failed: %s", #cond);                       \
            MX_LOG_ERROR("Location: %s:%d", __FILE__, __LINE__);               \
            MX_LOG_ERROR("" __VA_ARGS__);                                      \
            __builtin_trap();                                                  \
        }                                                                      \
    } while (0)
#endif

#else
#define MX_ASSERT(cond, ...) ((void)0)
#endif

#endif // MX_ASSERTS_H
