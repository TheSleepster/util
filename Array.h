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
template<typename type, uint32 Size>
struct array
{
    uint32 ElementSize;
    uint32 Capacity;
    uint32 Used;
    type   Elements[Size];
    array() : ElementSize(Size), Capacity(Size), Used(0) {}
    void Reset(){memset(Elements, 0, sizeof(type) * Capacity);}

    void
    Append(type *Element)
    {
        if(Used < Capacity) Elements[Used++] = *Element;
        else cl_Error("Array is full!\n");
    }

    type*
    operator[](uint32 Index)
    {
        if(Index < Capacity) return(&Elements[Index]);
        else
        {
            cl_Error("Array Index is out of bounds!\n");
            return(0);
        }
    }
};

#endif
