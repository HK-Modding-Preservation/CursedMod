#include "main.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _SignalCallback( int sigNum ) {
  printInFile( "Signal %d received", sigNum );
}
int _RegisterSignalCallbacks() {
  printInFile( "Registering %d signal callbacks...", NSIG );
  int amountRegistered = 0;

  for( int i = 0; i < NSIG; i++ ) {
    amountRegistered += signal( i, _SignalCallback ) != SIG_ERR;
  }

  printInFile( "%d signal callbacks registered!", amountRegistered );
  return amountRegistered;
}

extern bool Init() {
#if defined( CM_Gnu )
  openFile( true );
#endif
  printInFile( "Initializing library..." );

  if( _RegisterSignalCallbacks() <= 0 ) {
    printInFile( "Error registering signal callbacks!" );
    return false;
  }

  printInFile( "Library initialized!" );
  return true;
}

#if defined( CM_Win )
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

extern bool SetWindowDarkMode( const bool darkMode ) {
  printInFile( "SetWindowDarkMode(darkMode: %d) - Windows", darkMode );

  HWND unityWindowHandle = FindWindow( "UnityWndClass", "Hollow Knight" );
  printInFile( "HWND: %d", unityWindowHandle );

  printInFile( "Set window theme..." );

  COLORREF themeColor = darkMode ? 0x00505050 : 0x00FFFFFF;
  BOOL useDarkMode = darkMode;

  bool immersiveDarkModeResult
      = S_OK == DwmSetWindowAttribute( unityWindowHandle, CUSTOM_DWMWINDOWATTRIBUTE::DwmwaUseImmersiveDarkMode, &useDarkMode, sizeof( useDarkMode ) );
  bool immersiveDarkMode20h1Result
      = S_OK == DwmSetWindowAttribute( unityWindowHandle, CUSTOM_DWMWINDOWATTRIBUTE::DwmwaUseImmersiveDarkModeBefore20h1, &useDarkMode, sizeof( useDarkMode ) );
  bool borderColorResult = S_OK == DwmSetWindowAttribute( unityWindowHandle, CUSTOM_DWMWINDOWATTRIBUTE::DWMWA_BORDER_COLOR, &themeColor, sizeof( themeColor ) );
  bool captionColorResult
      = S_OK == DwmSetWindowAttribute( unityWindowHandle, CUSTOM_DWMWINDOWATTRIBUTE::DWMWA_CAPTION_COLOR, &themeColor, sizeof( themeColor ) );
  printInFile( "DwmSetWindowAttribute returned %d %d %d %d", immersiveDarkModeResult, immersiveDarkMode20h1Result, borderColorResult, captionColorResult );

  bool windowThemeResult = S_OK == SetWindowTheme( unityWindowHandle, L"Explorer", NULL );
  printInFile( "windowThemeResult returned %d", windowThemeResult );

  bool dwmColorChangedResult = S_OK != SendNotifyMessage( unityWindowHandle, WM_DWMCOLORIZATIONCOLORCHANGED, themeColor, 0 );
  printInFile( "dwmColorChangedResult returned %d", dwmColorChangedResult );

  tagRECT windowRect;
  GetWindowRect( unityWindowHandle, static_cast< LPRECT >( &windowRect ) );
  printInFile( "Got window rect: (%d, %d, %d, %d)", windowRect.top, windowRect.left, windowRect.right, windowRect.bottom );
  tagRECT adjustedRect;
  adjustedRect.top = 0;
  adjustedRect.left = 0;
  adjustedRect.right = windowRect.right - windowRect.left;
  adjustedRect.bottom = windowRect.bottom - windowRect.top;
  BOOL setPosResult = SetWindowPos( unityWindowHandle,
                                    HWND_BOTTOM,
                                    adjustedRect.top,
                                    adjustedRect.left,
                                    adjustedRect.right - 1,
                                    adjustedRect.bottom,
                                    SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER );
  SetWindowPos( unityWindowHandle,
                HWND_TOPMOST,
                adjustedRect.top,
                adjustedRect.left,
                adjustedRect.right,
                adjustedRect.bottom,
                SWP_DRAWFRAME | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER );
  printInFile( "SetWindowPos returned %d", setPosResult );
  return immersiveDarkModeResult || immersiveDarkMode20h1Result || borderColorResult || captionColorResult || windowThemeResult || dwmColorChangedResult;
}

extern bool SendShellNotification( const char *message ) {
  // hmm, somehow doesn't wanna work quite right
  printInFile( "SendShellNotification(message: '%ls') - Windows", message );

  HWND unityWindowHandle = FindWindow( "UnityWndClass", "Hollow Knight" );
  printInFile( "HWND: %d", unityWindowHandle );

  NOTIFYICONDATA notifyData{ sizeof( notifyData ) };
  printInFile( "notifyData.cbSize: %d", notifyData.cbSize );
  notifyData.hWnd = unityWindowHandle;
  printInFile( "notifyData.hWnd: %d", notifyData.hWnd );
  notifyData.uID = 0;
  printInFile( "notifyData.uID: %d", notifyData.uID );
  memset( notifyData.szInfo, 0, sizeof( notifyData.szInfo ) );
  sprintf( notifyData.szInfo, "%ls", message );
  printInFile( "notifyData.szInfo: '%s'", notifyData.szInfo );
  notifyData.dwState = NIS_HIDDEN;
  printInFile( "notifyData.dwState: %d", notifyData.dwState );
  notifyData.dwStateMask = NIS_HIDDEN;
  printInFile( "notifyData.dwStateMask: %d", notifyData.dwStateMask );
  notifyData.uTimeout = 30000;
  printInFile( "notifyData.uTimeout: %d", notifyData.uTimeout );
  memset( notifyData.szInfoTitle, 0, sizeof( notifyData.szInfoTitle ) );
  sprintf( notifyData.szInfoTitle, "%ls", "Hollow Knight" );
  // strcpy(notifyData.szInfoTitle, "Hollow Knight");
  printInFile( "notifyData.szInfoTitle: '%s'", notifyData.szInfoTitle );
  notifyData.dwInfoFlags = NIIF_INFO;
  printInFile( "notifyData.dwInfoFlags: %d", notifyData.dwInfoFlags );

  notifyData.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP | NIF_GUID;
  printInFile( "notifyData.uFlags: %d", notifyData.uFlags );

  bool notifyResult = Shell_NotifyIcon( NIM_ADD, &notifyData );
  printInFile( "notifyResult: %d", notifyResult );

  return notifyResult;
}

extern bool DoFunStuff() {
  printInFile( "DoFunStuff - Windows" );
  bool ret;
  char *currentDir = static_cast< char * >( calloc( MSG_SIZE, sizeof( char ) ) );
  if( GetCurrentDirectory( MSG_SIZE, currentDir ) != 0 ) {
    printInFile( "Current working dir: '%s'", currentDir );
    ret = true;
  } else {
    printInFile( "GetCurrentDirectory() error" );
    ret = false;
  }
  free( currentDir );
  return ret;
}
#endif
#if defined( CM_Gnu )
#include <unistd.h>

extern bool SetWindowDarkMode( bool darkMode ) {
  printInFile( "SetWindowDarkMode(darkMode: %d) - GNU", darkMode );
  return true;
}

extern bool SendShellNotification( const char *message ) {
  printInFile( "SendShellNotification(message: '%s') - GNU", message );
  return true;
}

extern bool DoFunStuff() {
  printInFile( "DoFunStuff - GNU" );
  bool ret;
  char *currentDir = static_cast< char * >( calloc( MSG_SIZE * 2, sizeof( char ) ) );
  if( getcwd( currentDir, MSG_SIZE ) != nullptr ) {
    printInFile( "Current working dir: '%s'", currentDir );
    ret = true;
  } else {
    printInFile( "getcwd() error" );
    ret = false;
  }
  return ret;
}
#endif
