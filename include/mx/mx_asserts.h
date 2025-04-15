#ifndef MX_ASSERTS_H
#define MX_ASSERTS_H

#include <assert.h>
#include <mx/mx_log.h>

#ifdef MX_DEBUG
#define MX_ASSERT(cond, ...)                                                \
    do {                                                                    \
        if (!(cond)) {                                                      \
            MX_LOG_ERROR("Assertion failed: %s", #cond);                    \
            MX_LOG_ERROR("" __VA_ARGS__);                                   \
            assert(cond);                                                   \
        }                                                                   \
    } while (0)
#else
#define MX_ASSERT(cond, ...) ((void)0)
#endif

#endif // MX_ASSERTS_H
