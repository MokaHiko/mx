#ifndef MX_H_
#define MX_H_

#include <stdint.h>
#include <stddef.h>

#ifndef MX_NULLABLE
    #ifdef __clang__
        #define MX_NULLABLE _Nullable
    #else
        #define MX_NULLABLE
    #endif
#endif

#ifndef MX_NOT_NULL
    #ifdef __clang__
        #define MX_NOT_NULL _Nonnull
    #else
        #define MX_NOT_NULL
    #endif
#endif

#ifndef MX_NO_DISCARD
    #ifdef __clang__
        #define MX_NO_DISCARD [[nodiscard]] 
    #else
        #define MX_NO_DISCARD
    #endif
#endif

#ifdef MX_EXPORTS
#ifdef MX_WIN32
	#define MX_API __declspec(dllexport)
#else 
	#define MX_API
#endif
#else
	#define MX_API
#endif

#if defined(_MSC_VER)
    #define MX_NO_VTABLE __declspec(novtable)
#else
    #define MX_NO_VTABLE
#endif

typedef enum mx_result {
    MX_SUCCESS = 0,

    MX_FAILURE,
    MX_INVALID_PARAMETER,
    MX_NULL_POINTER,
    MX_OUT_OF_MEMORY,

    MX_RESULT_MAX = 0xFF
} mx_result;

typedef uint32_t mx_bool;
#define MX_FALSE (uint32_t)0
#define MX_TRUE (uint32_t)1

#if defined(_WIN64)                       \
 || defined(__x86_64__) || defined(__ppc64__) \
 || defined(__aarch64__) || defined(__LP64__)
    #define MX_SYSTEM_64_BIT 1
#else
    #define MX_SYSTEM_64_BIT 0
#endif

#include <stdint.h>

#if MX_SYSTEM_64_BIT
    typedef uint64_t mx_ptr_t;
#else
    typedef uint32_t mx_ptr_t;
#endif

#define MX_ARRAY_COUNT(arr)                                                                                  \
    ((sizeof(arr) / sizeof((arr)[0])) +                                                                      \
     0 * sizeof(char[1 - 2 * __builtin_types_compatible_p(__typeof__(arr), __typeof__(&(arr)[0]))]))

#define mx_concat2(a, b) a##b
#define mx_concat(a, b)  mx_concat2(a, b)

// Create a unique name with line number
#define mx_macro_var_line(name) concat(name, __LINE__)

#endif
