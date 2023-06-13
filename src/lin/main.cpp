#include "../main.h"

#include <stdlib.h>
#include <string.h>

extern bool Init() {
  openFile( true );
  printInFile( "Initializing library..." );

  // notify_init( "CursedMod" );

  if( _RegisterSignalCallbacks() <= 0 ) {
    printInFile( "Error registering signal callbacks!" );
    return false;
  }

  printInFile( "Library initialized!" );
  return true;
}

extern bool Deinit() {
  printInFile( "Deinitializing library..." );

  closeFile();

  return true;
}

extern bool SetWindowDarkMode( const bool darkMode ) {
  printInFile( "SetWindowDarkMode(darkMode: %d) - Linux", darkMode );

  printInFile( "SetWindowDarkMode is unsupported on Linux" );

  return false;
}

extern bool SendShellNotification( char const* title, char const* message ) {
  printInFile( "SendShellNotification(title: '%s', message: '%s') - Linux", title, message );

  // notification = notify_notification_new( title, message, 0 );
  // notify_notification_set_timeout( notification, 10000 );  // 10 seconds
  // return notify_notification_show( n, 0 );
  printInFile( "SendShellNotification is unsupported on Linux" );

  return false;
}

extern bool RemoveShellNotification() {
  printInFile( "RemoveShellNotification - Linux" );

  printInFile( "RemoveShellNotification is unsupported on Linux" );

  return false;
}

extern bool DoFunStuff() {
  printInFile( "DoFunStuff - Linux" );

  bool ret = true;

  char* currentDir = static_cast< char* >( calloc( MSG_SIZE * 2, sizeof( char ) ) );
  if( getcwd( currentDir, MSG_SIZE ) != nullptr ) {
    printInFile( "Current working dir: '%s'", currentDir );
    ret = true;
  } else {
    printInFile( "getcwd() error" );
    ret = false;
  }
  free( currentDir );

  return ret;
}
