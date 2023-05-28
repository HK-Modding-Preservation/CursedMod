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
#if defined( CM_MacOS ) || defined( CM_Linux )
  openFile( true );
#endif
  printInFile( "Initializing library..." );

#if defined( CM_Windows )
  unityWindowHandle = FindWindow( "UnityWndClass", "Hollow Knight" );
  printInFile( "HWND: %d", unityWindowHandle );

  notifyData.cbSize = sizeof( notifyData );
  printInFile( "notifyData.cbSize: %d", notifyData.cbSize );
  notifyData.hWnd = unityWindowHandle;
  printInFile( "notifyData.hWnd: %d", notifyData.hWnd );
  notifyData.uID = 0;
  printInFile( "notifyData.uID: %d", notifyData.uID );
  notifyData.uTimeout = 30000;
  printInFile( "notifyData.uTimeout: %d", notifyData.uTimeout );
  notifyData.dwInfoFlags = NIIF_NONE;
  printInFile( "notifyData.dwInfoFlags: %d", notifyData.dwInfoFlags );
  notifyData.uFlags = NIF_INFO;
  printInFile( "notifyData.uFlags: %d", notifyData.uFlags );
#elif defined( CM_Linux )
  // notify_init( "CursedMod" );
#endif

  if( _RegisterSignalCallbacks() <= 0 ) {
    printInFile( "Error registering signal callbacks!" );
    return false;
  }

  printInFile( "Library initialized!" );
  return true;
}

extern bool SetWindowDarkMode( const bool darkMode ) {
#if defined( CM_Windows )
  printInFile( "SetWindowDarkMode(darkMode: %d) - Windows", darkMode );
#elif defined( CM_MacOS )
  printInFile( "SetWindowDarkMode(darkMode: %d) - MacOS", darkMode );
#elif defined( CM_Linux )
  printInFile( "SetWindowDarkMode(darkMode: %d) - Linux", darkMode );
#endif

  bool ret = true;

#if defined( CM_Windows )
  printInFile( "Set window theme..." );
  COLORREF themeColor = darkMode ? 0x00505050 : 0x00FFFFFF;
  BOOL useDarkMode = darkMode;
  bool immersiveDarkModeResult
      = S_OK == DwmSetWindowAttribute( unityWindowHandle, CUSTOM_DWMWINDOWATTRIBUTE::DWMA_USE_IMMERSIVE_DARKMODE, &useDarkMode, sizeof( useDarkMode ) );
  bool immersiveDarkMode20h1Result
      = S_OK
        == DwmSetWindowAttribute( unityWindowHandle, CUSTOM_DWMWINDOWATTRIBUTE::DWMA_USE_IMMERSIVE_DARKMODE_BEFORE20H1, &useDarkMode, sizeof( useDarkMode ) );
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
  ret = immersiveDarkModeResult || immersiveDarkMode20h1Result || borderColorResult || captionColorResult || windowThemeResult || dwmColorChangedResult;
#elif defined( CM_MacOS )
  printInFile( "SetWindowDarkMode is unsupported on MacOS" );
#elif defined( CM_Linux )
  printInFile( "SetWindowDarkMode is unsupported on Linux" );
#endif

  return ret;
}

extern bool SendShellNotification( const char *title, const char *message ) {
#if defined( CM_Windows )
  printInFile( "SendShellNotification(title: '%ls', message: '%ls') - Windows", title, message );
#elif defined( CM_MacOS )
  printInFile( "SendShellNotification(title: '%s', message: '%s') - MacOS", title, message );
#elif defined( CM_Linux )
  printInFile( "SendShellNotification(title: '%s', message: '%s') - Linux", title, message );
#endif

  bool ret = true;

#if defined( CM_Windows )
  memset( notifyData.szInfo, 0, sizeof( notifyData.szInfo ) );
  sprintf( notifyData.szInfo, "%ls", message );
  printInFile( "notifyData.szInfo: '%s'", notifyData.szInfo );
  memset( notifyData.szInfoTitle, 0, sizeof( notifyData.szInfoTitle ) );
  sprintf( notifyData.szInfoTitle, "%ls", title );
  printInFile( "notifyData.szInfoTitle: '%s'", notifyData.szInfoTitle );
  ret = Shell_NotifyIcon( NIM_ADD, &notifyData );
  printInFile( "notifyAddResult: %d", ret );
  if( !ret ) {
    RemoveShellNotification();
    ret = Shell_NotifyIcon( NIM_ADD, &notifyData );
    printInFile( "notifyAddResult: %d", ret );
  }
#elif defined( CM_MacOS )
  printInFile( "SendShellNotification is unsupported on MacOS" );
#elif defined( CM_Linux )
  // notification = notify_notification_new( title, message, 0 );
  // notify_notification_set_timeout( notification, 10000 );  // 10 seconds
  // ret = notify_notification_show( n, 0 );
  printInFile( "SendShellNotification is unsupported on Linux" );
#endif

  return ret;
}

extern bool RemoveShellNotification() {
#if defined( CM_Windows )
  printInFile( "RemoveShellNotification - Windows" );
#elif defined( CM_MacOS )
  printInFile( "RemoveShellNotification - MacOS" );
#elif defined( CM_Linux )
  printInFile( "RemoveShellNotification - Linux" );
#endif

  bool ret = true;

#if defined( CM_Windows )
  bool notifyDeleteResult = Shell_NotifyIcon( NIM_DELETE, &notifyData );
  printInFile( "notifyDeleteResult: %d", notifyDeleteResult );
  ret = notifyDeleteResult;
#elif defined( CM_MacOS )
  printInFile( "RemoveShellNotification is unsupported on MacOS" );
#elif defined( CM_Linux )
  printInFile( "RemoveShellNotification is unsupported on Linux" );
#endif

  return ret;
}

extern bool DoFunStuff() {
#if defined( CM_Windows )
  printInFile( "DoFunStuff - Windows" );
#elif defined( CM_MacOS )
  printInFile( "DoFunStuff - MacOS" );
#elif defined( CM_Linux )
  printInFile( "DoFunStuff - Linux" );
#endif

  bool ret = true;

#if defined( CM_Windows )
  char *currentDir = static_cast< char * >( calloc( MSG_SIZE, sizeof( char ) ) );
  if( GetCurrentDirectory( MSG_SIZE, currentDir ) != 0 ) {
    printInFile( "Current working dir: '%s'", currentDir );
    ret = true;
  } else {
    printInFile( "GetCurrentDirectory() error" );
    ret = false;
  }
  free( currentDir );
#elif defined( CM_MacOS )
  printInFile( "DoFunStuff is unsupported on MacOS" );
#elif defined( CM_Linux )
  char *currentDir = static_cast< char * >( calloc( MSG_SIZE * 2, sizeof( char ) ) );
  if( getcwd( currentDir, MSG_SIZE ) != nullptr ) {
    printInFile( "Current working dir: '%s'", currentDir );
    ret = true;
  } else {
    printInFile( "getcwd() error" );
    ret = false;
  }
#endif

  return ret;
}
