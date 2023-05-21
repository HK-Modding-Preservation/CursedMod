#ifndef CURSEDMODNATIVE_COMMON_H_
#define CURSEDMODNATIVE_COMMON_H_

#if defined(_WIN64)
//  Microsoft
#define CM_Win
#elif defined(_WIN32)
//  Microsoft
#define CM_Win
#elif defined(__GNUC__)
//  GCC
#define CM_Gnu
#else
//  do nothing and hope for the best?
#endif

#if defined(CM_Win)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(CM_Gnu)
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#else
#define EXPORT
#define IMPORT
#pragma warning Unknown dynamic link import / export semantics.
#endif

#define MSG_SIZE 256

#include <cstdio>
#include <utility>

FILE *logFile = nullptr;
void openFile(bool truncate) {
  const char *openMode = "a";
  if (truncate) {
    openMode = "w";
  }
  if (logFile == nullptr) {
    logFile = fopen("CursedMod-Native.log", openMode);
  }
}
void closeFile() {
  if (logFile != nullptr) {
    fclose(logFile);
    logFile = nullptr;
  }
}
void printInFile(const char *msg) {
  openFile(false);
  if (logFile != nullptr) {
    fprintf(logFile, msg);
    fprintf(logFile, "\n");
    fflush(logFile);
  }
}
template <typename... Args> void printInFile(const char *format, Args... args) {
  openFile(false);
  if (logFile != nullptr) {
    fprintf(logFile, format, std::forward<Args>(args)...);
    fprintf(logFile, "\n");
    fflush(logFile);
  }
}

#if defined(CM_Win)
//  Microsoft
#include <Windows.h>

extern "C" {
EXPORT BOOL WINAPI DllMain(HINSTANCE const dllModHandle, DWORD const callReason,
                           LPVOID const reserved) {
  switch (callReason) {
  case DLL_PROCESS_ATTACH:
    openFile(true);
    break;
  case DLL_THREAD_ATTACH:
    break;
  }
  printInFile("DllMain(dllModHandle: %d, callReason: %d, reserved: %d)",
              static_cast<void *>(const_cast<HINSTANCE>(dllModHandle)),
              callReason, static_cast<void *>(const_cast<LPVOID>(reserved)));
  switch (callReason) {
  case DLL_THREAD_DETACH:
    break;
  case DLL_PROCESS_DETACH:
    closeFile();
    break;
  }
  return TRUE;
}
EXPORT BOOL __stdcall _DllMainCRTStartup(HINSTANCE const dllModHandle,
                                         DWORD const callReason,
                                         LPVOID const reserved) {
  return DllMain(dllModHandle, callReason, reserved);
}
}
#endif

#endif // CURSEDMODNATIVE_COMMON_H_
