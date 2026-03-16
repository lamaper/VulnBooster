MULTIPROCESS_TEST_MAIN ( KilledChildProcess ) {
 WaitToDie ( ProcessUtilTest : : GetSignalFilePath ( kSignalFileKill ) . c_str ( ) ) ;

 : : TerminateProcess ( handle , kExpectedKilledExitCode ) ;


 }