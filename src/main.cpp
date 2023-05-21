#include "main.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _SignalCallback(int sigNum) { printInFile("Signal %d received", sigNum); }
int _RegisterSignalCallbacks() {
  printInFile("Registering %d signal callbacks...", NSIG);

  for (int i = 0; i < NSIG; i++) {
    signal(i, _SignalCallback);
  }

  printInFile("%d signal callbacks registered!", NSIG);

  return 0;
}

extern int Init() {
  printInFile("Initializing library...");

  if (_RegisterSignalCallbacks()) {
    printInFile("Error registering signal callbacks!");
    return 1;
  }

  printInFile("Library initialized!");
  return 0;
}

#ifdef CM_Win
#include <dwmapi.h>
#include <windows.h>

enum CUSTOM_DWMWINDOWATTRIBUTE : WORD {
  DWMWA_USE_HOSTBACKDROPBRUSH = 17,
  DwmwaUseImmersiveDarkModeBefore20h1 = 19,
  DwmwaUseImmersiveDarkMode = 20,
  DWMWA_WINDOW_CORNER_PREFERENCE = 33,
  DWMWA_BORDER_COLOR,
  DWMWA_CAPTION_COLOR,
  DWMWA_TEXT_COLOR,
  DWMWA_VISIBLE_FRAME_BORDER_THICKNESS,
  DWMWA_SYSTEMBACKDROP_TYPE
};

extern void SetDarkMode(bool darkMode) {
  printInFile("SetDarkMode(darkMode: %d) - Windows", darkMode);

  HWND unityWindowHandle = FindWindow("UnityWndClass", "Hollow Knight");

  printInFile("HWND: %d", unityWindowHandle);

  printInFile("Set window theme...");

  COLORREF themeColor = darkMode ? 0x00505050 : 0x00FFFFFF;
  BOOL useDarkMode = darkMode;

  BOOL immersiveDarkModeResult =
      S_OK == DwmSetWindowAttribute(
                  unityWindowHandle,
                  CUSTOM_DWMWINDOWATTRIBUTE::DwmwaUseImmersiveDarkMode,
                  &useDarkMode, sizeof(useDarkMode));
  BOOL immersiveDarkMode20h1Result =
      S_OK ==
      DwmSetWindowAttribute(
          unityWindowHandle,
          CUSTOM_DWMWINDOWATTRIBUTE::DwmwaUseImmersiveDarkModeBefore20h1,
          &useDarkMode, sizeof(useDarkMode));
  BOOL borderColorResult =
      S_OK ==
      DwmSetWindowAttribute(unityWindowHandle,
                            CUSTOM_DWMWINDOWATTRIBUTE::DWMWA_BORDER_COLOR,
                            &themeColor, sizeof(themeColor));
  BOOL captionColorResult =
      S_OK ==
      DwmSetWindowAttribute(unityWindowHandle,
                            CUSTOM_DWMWINDOWATTRIBUTE::DWMWA_CAPTION_COLOR,
                            &themeColor, sizeof(themeColor));
  printInFile("DwmSetWindowAttribute returned %d %d %d %d",
              immersiveDarkModeResult, immersiveDarkMode20h1Result,
              borderColorResult, captionColorResult);

  BOOL windowThemeResult =
      S_OK == SetWindowTheme(unityWindowHandle, L"Explorer", NULL);
  printInFile("windowThemeResult returned %d", windowThemeResult);

  BOOL dwmColorChangedResult =
      S_OK != SendNotifyMessage(unityWindowHandle,
                                WM_DWMCOLORIZATIONCOLORCHANGED, themeColor, 0);
  printInFile("dwmColorChangedResult returned %d", dwmColorChangedResult);

  tagRECT windowRect;
  GetWindowRect(unityWindowHandle, static_cast<LPRECT>(&windowRect));
  printInFile("Got window rect: (%d, %d, %d, %d)", windowRect.top,
              windowRect.left, windowRect.right, windowRect.bottom);
  tagRECT adjustedRect;
  adjustedRect.top = 0;
  adjustedRect.left = 0;
  adjustedRect.right = windowRect.right - windowRect.left;
  adjustedRect.bottom = windowRect.bottom - windowRect.top;
  BOOL setPosResult = SetWindowPos(
      unityWindowHandle, HWND_BOTTOM, adjustedRect.top, adjustedRect.left,
      adjustedRect.right - 1, adjustedRect.bottom,
      SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER);
  SetWindowPos(unityWindowHandle, HWND_TOPMOST, adjustedRect.top,
               adjustedRect.left, adjustedRect.right, adjustedRect.bottom,
               SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER);
  printInFile("SetWindowPos returned %d", setPosResult);
}

extern void DoFunStuff() {
  printInFile("DoFunStuff - Windows");

  char *currentDir = static_cast<char *>(calloc(MSG_SIZE, sizeof(char)));
  if (GetCurrentDirectory(MSG_SIZE, currentDir) != 0) {
    printInFile("Current working dir: '%s'", currentDir);
  } else {
    printInFile("GetCurrentDirectory() error");
  }
  free(currentDir);
}
#endif
#ifdef CM_Gnu
#include <unistd.h>

extern void SetDarkMode(bool darkMode) {
  printInFile("SetDarkMode(darkMode: %d) - GNU", darkMode);
}

extern void DoFunStuff() {
  printInFile("DoFunStuff - GNU");

  char *currentDir = static_cast<char *>(calloc(MSG_SIZE * 2, sizeof(char)));

  if (getcwd(currentDir, MSG_SIZE) != nullptr) {
    printInFile("Current working dir: '%s'", currentDir);
  } else {
    printInFile("getcwd() error");
  }
}
#endif
