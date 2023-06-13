#ifndef CURSEDMODNATIVE_MAIN_H_
#define CURSEDMODNATIVE_MAIN_H_

#include "common.h"

void _SignalCallback( const int sigNum );
int _RegisterSignalCallbacks();

#if defined( CM_Windows )
#include <dwmapi.h>
#include <windows.h>
enum CUSTOM_DWMWINDOWATTRIBUTE : WORD {
  DWMWA_USE_HOSTBACKDROPBRUSH = 17,
  DWMA_USE_IMMERSIVE_DARKMODE_BEFORE20H1 = 19,
  DWMA_USE_IMMERSIVE_DARKMODE = 20,
  DWMWA_WINDOW_CORNER_PREFERENCE = 33,
  DWMWA_BORDER_COLOR,
  DWMWA_CAPTION_COLOR,
  DWMWA_TEXT_COLOR,
  DWMWA_VISIBLE_FRAME_BORDER_THICKNESS,
  DWMWA_SYSTEMBACKDROP_TYPE
};
extern HWND unityWindowHandle;
extern NOTIFYICONDATA notifyData;
#elif defined( CM_MacOS )
#include <unistd.h>
#elif defined( CM_Linux )
#include <gio/gio.h>
#include <unistd.h>
// NotifyNotification *notification;
#endif

extern "C" EXPORT bool Init();
extern "C" EXPORT bool Deinit();
extern "C" EXPORT bool SetWindowDarkMode( const bool darkMode );
extern "C" EXPORT bool SendShellNotification( char const *title, char const *message );
extern "C" EXPORT bool RemoveShellNotification();
extern "C" EXPORT bool DoFunStuff();

#endif  // CURSEDMODNATIVE_MAIN_H_
