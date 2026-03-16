MULTIPROCESS_TEST_MAIN ( CrashingChildProcess ) {
 WaitToDie ( ProcessUtilTest : : GetSignalFilePath ( kSignalFileCrash ) . c_str ( ) ) ;


 * oops = 0xDEAD ;
 return 1 ;
 }