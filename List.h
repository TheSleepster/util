#if !defined(LIST_H)
/* ========================================================================
   $File: List.h $
   $Date: Wed, 25 Dec 24: 08:47PM $
   $Revision: $
   $Creator: Justin Lewis $
   ======================================================================== */

#define LIST_H
#include "util/Arena.h"
#include "types.h"

struct list
{
    uint32 Capacity;
    uint32 Used;
    uint32 ElementSize;
    void  *Data;
};

internal list*
ListCreate(memory_arena *Arena, memory_index ElementSize)
{
}

#endif
