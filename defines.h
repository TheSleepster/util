#if !defined(DEFINES_H)
/* ========================================================================
   $File: defines.h $
   $Date: Fri, 27 Dec 24: 08:37AM $
   $Revision: $
   $Creator: Justin Lewis $
   ======================================================================== */

#define DEFINES_H

#define ArrayCount(Array) (sizeof(Array) / sizeof(Array[0]))

#if _MSC_VER
#define alignas(x)       __declspec(align(x))
#define inline           __forceinline

// TODO(Sleepster): Double check this stuff
#define WriteBarrier     _WriteBarrier(); _mm_sfence()
#define ReadBarrier      _ReadBarrier();  _mm_sfence()
#define ReadWriteBarrier _ReadWriteBarrier(); _mm_lfence()

#include <intrin.h>
inline int32 AtomicCompareExchange32(int32 volatile *Target, int32 Expected, int32 Value)
{
    int32 Result = _InterlockedCompareExchange((long *)Target, Expected, Value);
    return(Result);
}
#else
#define alignas(x)       alignas(x)
#define inline           inline

#define WriteBarrier     __atomic_signal_fence(__ATOMIC_RELEASE); __atomic_thread_fence(__ATOMIC_RELEASE)
#define ReadBarrier      __atomic_signal_fence(__ATOMIC_ACQUIRE); __atomic_thread_fence(__ATOMIC_ACQUIRE)
#define ReadWriteBarrier __atomic_signal_fence(__ATOMIC_ACQ_REL); __atomic_thread_fence(__ATOMIC_ACQ_REL)
#endif

#endif
