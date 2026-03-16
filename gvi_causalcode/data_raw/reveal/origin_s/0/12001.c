TEST_F ( ProcessUtilTest , GetTerminationStatusKill ) {
 const std : : string signal_file = ProcessUtilTest : : GetSignalFilePath ( kSignalFileKill ) ;
 remove ( signal_file . c_str ( ) ) ;
 base : : Process process = SpawnChild ( "KilledChildProcess" ) ;
 ASSERT_TRUE ( process . IsValid ( ) ) ;
 int exit_code = 42 ;
 EXPECT_EQ ( base : : TERMINATION_STATUS_STILL_RUNNING , base : : GetTerminationStatus ( process . Handle ( ) , & exit_code ) ) ;
 EXPECT_EQ ( kExpectedStillRunningExitCode , exit_code ) ;
 SignalChildren ( signal_file . c_str ( ) ) ;
 exit_code = 42 ;
 base : : TerminationStatus status = WaitForChildTermination ( process . Handle ( ) , & exit_code ) ;
 EXPECT_EQ ( base : : TERMINATION_STATUS_PROCESS_WAS_KILLED , status ) ;


 EXPECT_NE ( 0 , signaled ) ;
 int signal = WTERMSIG ( exit_code ) ;
 EXPECT_EQ ( SIGKILL , signal ) ;

 }