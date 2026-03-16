TEST_F ( ProcessUtilTest , KillSlowChild ) {
 const std : : string signal_file = ProcessUtilTest : : GetSignalFilePath ( kSignalFileSlow ) ;
 remove ( signal_file . c_str ( ) ) ;
 base : : Process process = SpawnChild ( "SlowChildProcess" ) ;
 ASSERT_TRUE ( process . IsValid ( ) ) ;
 SignalChildren ( signal_file . c_str ( ) ) ;
 EXPECT_TRUE ( base : : WaitForSingleProcess ( process . Handle ( ) , TestTimeouts : : action_max_timeout ( ) ) ) ;
 remove ( signal_file . c_str ( ) ) ;
 }