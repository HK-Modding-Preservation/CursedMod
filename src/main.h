#ifndef CURSEDMODNATIVE_MAIN_H_
#define CURSEDMODNATIVE_MAIN_H_

#include "common.h"

void _SignalCallback( const int sigNum );
int _RegisterSignalCallbacks();

#if defined( CM_Win )
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
HWND unityWindowHandle;
NOTIFYICONDATA notifyData;
#endif
extern "C" EXPORT bool Init();
extern "C" EXPORT bool SetWindowDarkMode( const bool darkMode );
extern "C" EXPORT bool SendShellNotification( const char *title, const char *message );
extern "C" EXPORT bool RemoveShellNotification();
extern "C" EXPORT bool DoFunStuff();

#endif  // CURSEDMODNATIVE_MAIN_H_
