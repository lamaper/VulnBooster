TEST_F ( ProcessUtilTest , DISABLED_GetTerminationStatusExit ) {
 const std : : string signal_file = ProcessUtilTest : : GetSignalFilePath ( kSignalFileSlow ) ;
 remove ( signal_file . c_str ( ) ) ;
 base : : Process process = SpawnChild ( "SlowChildProcess" ) ;
 ASSERT_TRUE ( process . IsValid ( ) ) ;
 int exit_code = 42 ;
 EXPECT_EQ ( base : : TERMINATION_STATUS_STILL_RUNNING , base : : GetTerminationStatus ( process . Handle ( ) , & exit_code ) ) ;
 EXPECT_EQ ( kExpectedStillRunningExitCode , exit_code ) ;
 SignalChildren ( signal_file . c_str ( ) ) ;
 exit_code = 42 ;
 base : : TerminationStatus status = WaitForChildTermination ( process . Handle ( ) , & exit_code ) ;
 EXPECT_EQ ( base : : TERMINATION_STATUS_NORMAL_TERMINATION , status ) ;
 EXPECT_EQ ( 0 , exit_code ) ;
 remove ( signal_file . c_str ( ) ) ;
 }