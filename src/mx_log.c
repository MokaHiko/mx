#include <mx/mx_log.h>
#include <stdarg.h>
#include <stdio.h>

// ANSI color codes for terminal output
const char* MX_LOG_COLOR_DEBUG   = "\033[0;37m"; // White/Gray
const char* MX_LOG_COLOR_INFO    = "\033[0;36m"; // Cyan
const char* MX_LOG_COLOR_TRACE   = "\033[0;37m"; // White/Gray
const char* MX_LOG_COLOR_WARN    = "\033[0;33m"; // Yellow
const char* MX_LOG_COLOR_ERROR   = "\033[0;31m"; // Red
const char* MX_LOG_COLOR_SUCCESS = "\033[0;32m"; // Green
const char* MX_LOG_COLOR_RESET   = "\033[0m";    // Reset to default

void mx_log(mx_log_level level, const char* fmt, ...) {
    const char* level_str;
    const char* color;

    switch (level) {
    case MX_LOG_LEVEL_DEBUG:
        level_str = "DEBUG";
        color     = MX_LOG_COLOR_DEBUG;
        break;
    case MX_LOG_LEVEL_INFO:
        level_str = "INFO";
        color     = MX_LOG_COLOR_INFO;
        break;
    case MX_LOG_LEVEL_WARN:
        level_str = "WARN";
        color     = MX_LOG_COLOR_WARN;
        break;
    case MX_LOG_LEVEL_ERROR:
        level_str = "ERROR";
        color     = MX_LOG_COLOR_ERROR;
        break;

    case MX_LOG_LEVEL_SUCCESS:
        level_str = "SUCCESS";
        color     = MX_LOG_COLOR_SUCCESS;
        break;

    case MX_LOG_LEVEL_TRACE:
    default:
        level_str = "LOG";
        color     = MX_LOG_COLOR_INFO;
        break;
    }

    printf("%s [%s] ", color, level_str);

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("%s\n", MX_LOG_COLOR_RESET);
}
