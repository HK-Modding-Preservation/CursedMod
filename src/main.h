#ifndef CURSEDMODNATIVE_MAIN_H_
#define CURSEDMODNATIVE_MAIN_H_

#include "common.h"

void _SignalCallback( const int sigNum );
int _RegisterSignalCallbacks();

extern "C" EXPORT bool Init();
extern "C" EXPORT bool SetWindowDarkMode( const bool darkMode );
extern "C" EXPORT bool SendShellNotification( const char *message );
extern "C" EXPORT bool DoFunStuff();

#endif  // CURSEDMODNATIVE_MAIN_H_
