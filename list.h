#if !defined(LIST_H)
/* ========================================================================
   $File: List.h $
   $Date: Wed, 25 Dec 24: 08:47PM $
   $Revision: $
   $Creator: Justin Lewis $
   ======================================================================== */

#define LIST_H
#include "arena.h"
#include "debug.h"
#include "types.h"

constexpr int32 LIST_GROW_FACTOR  = 2;
constexpr int32 DEFAULT_LIST_SIZE = 20;

// NOTE(Sleepster): This is created outside of the normal memory
// allocation strategy, therefore we should use it very sparingly
struct list
{
    uint64  Capacity;
    uint64  Used;
    uint64  Stride;
    uint32  GrowFactor;

    void   *Elements;
};

#define ListCreate(type, capacity) _ListCreate(sizeof(type), capacity)

internal list
_ListCreate(uint64 ElementSize, uint64 Capacity = DEFAULT_LIST_SIZE, int32 GrowFactor = LIST_GROW_FACTOR)
{
    list Result       = {};
    Result.Capacity   = Capacity;
    Result.Stride     = ElementSize;
    Result.Used       = 0;
    Result.GrowFactor = GrowFactor;
    Result.Elements   = malloc((ElementSize * Capacity));
    Log(LOG_TRACE, "List created...");

    return(Result);
}

internal void
ListDestroy(list *List)
{
    free(List->Elements);
    List->Used     = 0;
    List->Stride   = 0;
    List->Capacity = 0;
    Log(LOG_TRACE, "List has been destroyed...");
}

// NOTE(Sleepster): This will always copy by value
internal inline void
ListAppendValue(list *List, auto Value)
{
    if(List->Used + 1 >= List->Capacity)
    {
        ListGrow(List);
    }
    uint8 *ValueToAppend = (uint8 *)List->Elements + (List->Used * List->Stride);
    memcpy(ValueToAppend, &Value, List->Stride);
    ++List->Used;
}


internal inline void
ListGrow(list *List)
{
    void *NewElements = malloc(List->Stride * (List->Capacity * List->GrowFactor));
    Assert(NewElements, "NewElements Failed to Alloc...\n");

    memcpy(List->Elements, NewElements, List->Stride * List->Capacity);
    free(List->Elements);
        
    List->Capacity *= List->GrowFactor;
    List->Elements = NewElements;
}

internal inline void*
ListGetValueAtIndex(list *List, int32 Index)
{
    if(Index >= List->Capacity)
    {
        Log(LOG_ERROR, "Index '%d' is invalid... List capacity is '%'...", Index, List->Capacity);
        return(nullptr);
    }
    uint8 *Value = (uint8 *)List->Elements + (Index * List->Stride);
    return(Value);
}

internal inline bool8 
ListSetValueAtIndex(list *List, int32 Index, void *Value)
{
    if(Index >= List->Capacity)
    {
        Log(LOG_ERROR, "Failed to set value at index '%d', index is invalid!...", Index);
        return(false);
    }
    
    uint8 *ListValue = (uint8 *)List->Elements + (Index * List->Stride);
    ListValue = (uint8 *)Value;

    return(true);
}

internal bool8 
ListRemoveValueAtIndex(list *List, int32 Index)
{
    if(Index > List->Capacity)
    {
        Log(LOG_ERROR, "Index '%' is larger than the List's capacity!...", Index);
        return(false);
    }

    if(List->Used == 1)
    {
        List->Used = 0;
        return(true);
    }

    --List->Used;
    uint8 *ElementPtr = (uint8*)List->Elements + (Index * List->Stride);
    uint8 *DataEndPtr = (uint8*)List->Elements + (List->Capacity * List->Stride);
    memcpy(ElementPtr, DataEndPtr, List->Stride);

    return(true);
}

// IMPORTANT(Sleepster): If you use this, the "Used" value of the list no longer matters...
internal inline void 
ListInsertValueAtIndex(list *List, int32 Index, void *Value)
{
    bool8 IndexIsValid = (Index > List->Capacity);
    while(!IndexIsValid)
    {
        ListGrow(List);
        if(Index < List->Capacity) break;
    }

    uint8 *Valueptr = (uint8 *)List->Elements + (List->Stride * Index);
    memcpy(Value, Valueptr, List->Stride);
}

internal inline void
ListReset(list *List)
{
    List->Used = 0;
    memset(List->Elements, 0, List->Stride * List->Capacity);
}

#endif
