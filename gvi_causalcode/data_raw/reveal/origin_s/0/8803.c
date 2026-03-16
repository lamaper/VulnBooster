MULTIPROCESS_TEST_MAIN ( SlowChildProcess ) {
 WaitToDie ( ProcessUtilTest : : GetSignalFilePath ( kSignalFileSlow ) . c_str ( ) ) ;
 return 0 ;
 }