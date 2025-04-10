#ifndef MX_LOG_H_
#define MX_LOG_H_

#include <mx/mx.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MX_LOG_LEVEL_TRACE,
    MX_LOG_LEVEL_INFO,
    MX_LOG_LEVEL_DEBUG,
    MX_LOG_LEVEL_WARN,
    MX_LOG_LEVEL_ERROR,
    MX_LOG_LEVEL_SUCCESS,
} mx_log_level;

MX_API void mx_log(mx_log_level level, const char* fmt, ...);

#ifdef __cplusplus
}
#endif

// Variadic macros (handles empty __VA_ARGS__ safely in C++)
/*#define MX_LOG_TRACE(...) mx_log(MX_LOG_LEVEL_TRACE, ##__VA_ARGS__)*/
#define MX_LOG_TRACE(...)

#define MX_LOG_INFO(...)  mx_log(MX_LOG_LEVEL_INFO,  ##__VA_ARGS__)
#define MX_LOG_DEBUG(...) mx_log(MX_LOG_LEVEL_DEBUG, ##__VA_ARGS__)
#define MX_LOG_WARN(...)  mx_log(MX_LOG_LEVEL_WARN,  ##__VA_ARGS__)
#define MX_LOG_ERROR(...) mx_log(MX_LOG_LEVEL_ERROR, ##__VA_ARGS__)
#define MX_LOG_SUCCESS(...) mx_log(MX_LOG_LEVEL_SUCCESS, ##__VA_ARGS__)

#endif /* MX_LOG_H_ */
