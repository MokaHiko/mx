#ifndef MX_H_
#define MX_H_

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

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

#define MX_SUCCESS (uint16_t)0

typedef uint32_t mx_bool;
#define MX_FALSE (uint32_t)0
#define MX_TRUE (uint32_t)1

#endif
