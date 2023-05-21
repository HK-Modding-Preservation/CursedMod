#ifndef CURSEDMODNATIVE_MAIN_H_
#define CURSEDMODNATIVE_MAIN_H_

#include "common.h"

void _SignalCallback(const int sigNum);
int _RegisterSignalCallbacks();

extern "C" EXPORT int Init();
extern "C" EXPORT void SetDarkMode(bool darkMode);
extern "C" EXPORT void DoFunStuff();

#endif // CURSEDMODNATIVE_MAIN_H_
