#include "../main.h"

#include <stdlib.h>
#include <string.h>

extern bool Init() {
  openFile( true );
  printInFile( "Initializing library..." );

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
  printInFile( "SetWindowDarkMode(darkMode: %d) - MacOS", darkMode );

  printInFile( "SetWindowDarkMode is unsupported on MacOS" );

  return false;
}

extern bool SendShellNotification( const char* title, const char* message ) {
  printInFile( "SendShellNotification(title: '%s', message: '%s') - MacOS", title, message );

  printInFile( "SendShellNotification is unsupported on MacOS" );

  return false;
}

extern bool RemoveShellNotification() {
  printInFile( "RemoveShellNotification - MacOS" );

  printInFile( "RemoveShellNotification is unsupported on MacOS" );

  return false;
}

extern bool DoFunStuff() {
  printInFile( "DoFunStuff - MacOS" );

  printInFile( "DoFunStuff is unsupported on MacOS" );

  return false;
}
