#if !defined(DEBUG_H)
/* ========================================================================
   $File: debug.h $
   $Date: Fri, 27 Dec 24: 07:54AM $
   $Revision: $
   $Creator: Justin Lewis $
   ======================================================================== */

#define DEBUG_H

#ifdef INTERNAL_DEBUG

#ifdef _WIN64
#define Check(Expression, Message, ...) if(!(Expression)) {char CHECKBUFFER[1024] = {}; sprintf(CHECKBUFFER, Message, __VA_ARGS__); printf("%s\n", CHECKBUFFER); fflush(stdout); __debugbreak();}
#define Assert(Expression) if(!(Expression)) {__debugbreak();}
#define Trace(Message) {printm(Message)}
#define printm(Message, ...)   {char BUFFER[128]  = {}; if(strlen(Message) > sizeof(BUFFER)) {Check(0, "[ERROR]: String is too large\n")}; sprintf(BUFFER, Message, ##__VA_ARGS__); printf("%s\n", BUFFER); fflush(stdout);}
#define printlm(Message, ...)  {char BUFFER[5192] = {}; if(strlen(Message) > sizeof(BUFFER)) {Check(0, "[ERROR]: String is too large\n")}; sprintf(BUFFER, Message, ##__VA_ARGS__); printf("%s\n", BUFFER); fflush(stdout);}
#define cl_Error(Message, ...) {char BUFFER[512]  = {}; if(strlen(Message) > sizeof(BUFFER)) {Check(0, "[ERROR]: String is too large\n")}; sprintf(BUFFER, Message, ##__VA_ARGS__); printf("[ERROR]: %s\n", BUFFER);  fflush(stdout); Assert(0);}
#define cl_Info(Message, ...)  {char BUFFER[512]  = {}; if(strlen(Message) > sizeof(BUFFER)) {Check(0, "[ERROR]: String is too large\n")}; sprintf(BUFFER, Message, ##__VA_ARGS__); printf("[INFO]: %s\n", BUFFER); fflush(stdout);}
#define InvalidCodePath __debugbreak()

#elif __linux__
#include <csignal>
#define Check(Expression, Message, ...) if(!(Expression)) {char CHECKBUFFER[1024] = {}; sprintf(CHECKBUFFER, Message, ##__VA_ARGS__); printf("%s\n", CHECKBUFFER); raise(SIGTRAP); fflush(stdout);}
#define Assert(Expression) if(!(Expression)) {raise(SIGTRAP);}
#define Trace(Message) {printm(Message)}
#define printm(Message, ...)   {char BUFFER[128]  = {}; if(strlen(Message) > sizeof(BUFFER)) {Check(0, "[ERROR]: String is too large\n")}; sprintf(BUFFER, Message, ##__VA_ARGS__); printf("%s\n", BUFFER);}
#define printlm(Message, ...)  {char BUFFER[5192] = {}; if(strlen(Message) > sizeof(BUFFER)) {Check(0, "[ERROR]: String is too large\n")}; sprintf(BUFFER, Message, ##__VA_ARGS__); printf("%s\n", BUFFER);}
#define cl_Error(Message, ...) {char BUFFER[512]  = {}; if(strlen(Message) > sizeof(BUFFER)) {Check(0, "[ERROR]: String is too large\n")}; sprintf(BUFFER, Message, ##__VA_ARGS__); printf("[ERROR]: %s\n", BUFFER); Assert(0);}
#define cl_Info(Message, ...)  {char BUFFER[512]  = {}; if(strlen(Message) > sizeof(BUFFER)) {Check(0, "[ERROR]: String is too large\n")}; sprintf(BUFFER, Message, ##__VA_ARGS__); printf("[INFO]: %s\n", BUFFER);}
#define InvalidCodePath raise(SIGTRAP)

#elif __APPLE__
#define Assert(Expression)
#define Check(Expression, Message, ...)
#define Trace(Message)
#define printm(Message, ...)
#define printlm(Message, ...)
#define cl_Error(Message, ...)
#define cl_Info(Message, ...) 
#define InvalidCodePath
#endif

#else

#define Assert(Expression)
#define Check(Expression, Message, ...)
#define Trace(Message)
#define printm(Message, ...)
#define printlm(Message, ...)
#define cl_Error(Message, ...)
#define cl_Info(Message, ...) 
#define InvalidCodePath

#endif

#endif
