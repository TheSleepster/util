#if !defined(LIST_H)
/* ========================================================================
   $File: List.h $
   $Date: Wed, 25 Dec 24: 08:47PM $
   $Revision: $
   $Creator: Justin Lewis $
   ======================================================================== */

#define LIST_H
#include "arena.h"
#include "types.h"

constexpr int32 DEFAULT_CAPACITY = 10;

// NOTE(Sleepster): Dynamic array
struct list
{
    uint32 Capacity;
    uint32 Used;
    uint32 ElementSize;
    void  *Data;
};

#define InitList(type) InitList_(sizeof(type));

internal list
InitList_(memory_index ElementSize)
{
    list Result      = {};
    Result.Capacity    = DEFAULT_CAPACITY;
    Result.Used        = 0;
    Result.ElementSize = ElementSize;
    Result.Data        = malloc(ElementSize * DEFAULT_CAPACITY);
    return(Result);
}

internal void
ListAppend(list *List, void *Element)
{
    if(List->Used == List->Capacity)
    {
        List->Capacity = List->Capacity > 0 ? List->Capacity * 2 : 1;
        void *Data = realloc(List->Data, List->ElementSize * List->Capacity);
        if(!Data)
        {
            cl_Error("Failure to realloc the list...\n");
        }

        List->Data = Data;
    }
    uint32 Index = List->Used++;
    memcpy((uint8*)List->Data + (Index * List->ElementSize), Element, List->ElementSize);
}

internal void*
ListGetIndex(list *List, int32 Index)
{
    Assert(Index > 0);
    if(Index < List->Capacity)
    {
        return((uint8*)List->Data + (Index * List->ElementSize));
    }
    else
    {
        printf("Index: %d, is out of bounds...\n", Index);
        return(0);
    }
}

// NOTE(Sleepster): This is a swap and pop method, swaps what's at the end of the list with the current index 
internal bool8 
ListRemoveIndex(list *List, int32 Index)
{
    Check(List->Used != 0, "List Is Empty...\n");
    if(Index < List->Used)
    {
        if(List->Used == 1)
        {
            List->Used = 0;
            return(1);
        }

        --List->Used;
        uint8 *ElementPtr = (uint8*)List->Data + (Index * List->ElementSize);
        uint8 *DataEndPtr = (uint8*)List->Data + (List->Capacity * List->ElementSize);
        memcpy(ElementPtr, DataEndPtr, List->ElementSize);
    }
    else
    {
        cl_Error("Cannot remove, index is currently unused...\n");
    }
    return(1);
}

#endif
