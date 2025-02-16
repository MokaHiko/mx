#ifndef MX_H_
#define MX_H_

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

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

#define MX_SUCESS (uint16_t)0

#endif
