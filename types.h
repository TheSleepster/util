#if !defined(TYPES_H)
/* ========================================================================
   $File: types.h $
   $Date: Fri, 27 Dec 24: 07:53AM $
   $Revision: $
   $Creator: Justin Lewis $
   ======================================================================== */

#define TYPES_H
#include <stdint.h>

#define global_variable static
#define local_persist   static
#define internal        static

#define external extern "C"

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;
typedef int64_t  int64;
typedef size_t   usize;

typedef int8     bool8;
typedef int32    bool32;

typedef float    real32;
typedef double   real64;

#define KB(Value) ((uint64)(Value) * 1024)
#define MB(Value) ((uint64)KB(Value) * 1024)
#define GB(Value) ((uint64)MB(Value) * 1024)

#endif
