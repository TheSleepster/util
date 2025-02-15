#if !defined(ARRAY_H)
/* ========================================================================
   $File: Array.h $
   $Date: Wed, 25 Dec 24: 07:44PM $
   $Revision: $
   $Creator: Justin Lewis $
   ======================================================================== */

#define ARRAY_H
#include "types.h"
#include "debug.h"

// NOTE(Sleepster): This is limited to the stack
struct array
{
    uint32 ElementSize;
    uint32 Capacity;
    uint32 Used;
    void  *Data;
};

#define InitArray(arena, type, count) InitArray_(arena, sizeof(type), count) 

internal inline array
InitArray_(int32 ElementSize, int32 Capacity)
{
    array Result = {};
    Result.ElementSize = ElementSize;
    Result.Capacity    = Capacity;
    Result.Used        = 0;
    Result.Data        = PushSize(ElementSize * Capacity);

    return(Result);
}

internal void *
GetArrayIndex(array *Array, int32 Index)
{
    if(Index < Array->Capacity)
    {
        return((uint8 *)Array->Data + (Index * Array->ElementSize));
    }
    else
    {
        Log(DEBUG_ERROR, "Target Index is out of range...\n");
        return(0);
    }
}

#endif
