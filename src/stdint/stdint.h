typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed long int int32_t;
typedef unsigned long int uint32_t;
typedef signed long long int int64_t;
typedef unsigned long long int uint64_t; // C17 standard types

#ifndef __cplusplus
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L
typedef uint8_t bool; // compiler complains if bool is not defined
#endif
#endif

#define true 1
#define false 0
