#if !defined(DEBUG_H)
/* ========================================================================
   $File: debug.h $
   $Date: Fri, 27 Dec 24: 07:54AM $
   $Revision: $
   $Creator: Justin Lewis $
   ======================================================================== */

#define DEBUG_H
#include "types.h"
#include <stdarg.h>
#include <stdio.h>
#include <cstring>

#ifdef _MSC_VER
#include <intrin.h>
#define DebugHalt() __debugbreak()
#else
#define DebugHalt() __builtin_trap()
#endif

#ifdef INTERNAL_DEBUG
#define Assert(Condition, Message, ...)                                                 \
{                                                                                       \
    if (!(Condition))                                                                   \
    {                                                                                   \
        Log(LOG_FATAL, "Assertion failed:\n (%s) " Message, #Condition, ##__VA_ARGS__); \
        DebugHalt();                                                                    \
    }                                                                                   \
}
#else
#define Assert(Condition, Message, ...)
#endif

#define InvalidCodePath DebugHalt()
enum debug_log_level
{
    LOG_TRACE,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
};

#define Log(Level, Message, ...) _Log(Level, Message, __FILE__, __LINE__, ##__VA_ARGS__)

internal void
_Log(debug_log_level LogLevel, const char *Message, char *File, int32 Line, ...)
{
    const char *InfoStrings[] = {"[TRACE]: ", "[INFO]: ", "[WARNING]:", "[NON-FATAL ERROR]: ", "[FATAL ERROR]: "};
    const char *ColorCodes[]  =
    {
        "\033[34m",          // LOG_TRACE: Blue
        "\033[32m",          // LOG_INFO: Green
        "\033[33m",          // LOG_WARNING: Yellow
        "\033[31m",          // LOG_ERROR: Red
        "\033[41m\033[30m"   // LOG_FATAL: Red background, Black text
    };
    bool8 IsError = (LogLevel > 2);

    char Buffer[32000];
    memset(Buffer, 0, sizeof(Buffer));

    va_list ArgPtr;
    va_start(ArgPtr, Line);
    vsnprintf(Buffer, sizeof(Buffer), Message, ArgPtr);
    va_end(ArgPtr);

    char OutBuffer[32000];
    memset(OutBuffer, 0, sizeof(OutBuffer));

    if(IsError)
    {
        sprintf(OutBuffer, "%s%s[File: %s, Line %d] %s\033[0m\n", ColorCodes[LogLevel], InfoStrings[LogLevel], File, Line, Buffer);
    }
    else
    {
        sprintf(OutBuffer, "%s%s%s\033[0m\n", ColorCodes[LogLevel], InfoStrings[LogLevel], Buffer);
    }

    printf("%s", OutBuffer);
}
#endif
