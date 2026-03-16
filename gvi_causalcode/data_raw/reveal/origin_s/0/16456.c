IN_PROC_BROWSER_TEST_F ( ProfileBrowserTest , ExitType ) {
 base : : ScopedTempDir temp_dir ;
 ASSERT_TRUE ( temp_dir . CreateUniqueTempDir ( ) ) ;
 MockProfileDelegate delegate ;
 EXPECT_CALL ( delegate , OnProfileCreated ( testing : : NotNull ( ) , true , true ) ) ;
 {
 std : : unique_ptr < Profile > profile ( CreateProfile ( temp_dir . path ( ) , & delegate , Profile : : CREATE_MODE_SYNCHRONOUS ) ) ;
 PrefService * prefs = profile -> GetPrefs ( ) ;
 std : : string crash_value ( prefs -> GetString ( prefs : : kSessionExitType ) ) ;
 profile -> SetExitType ( Profile : : EXIT_SESSION_ENDED ) ;
 std : : string first_call_value ( prefs -> GetString ( prefs : : kSessionExitType ) ) ;
 EXPECT_NE ( crash_value , first_call_value ) ;
 profile -> SetExitType ( Profile : : EXIT_NORMAL ) ;
 std : : string second_call_value ( prefs -> GetString ( prefs : : kSessionExitType ) ) ;
 EXPECT_EQ ( first_call_value , second_call_value ) ;
 profile -> SetExitType ( Profile : : EXIT_CRASHED ) ;
 std : : string final_value ( prefs -> GetString ( prefs : : kSessionExitType ) ) ;
 EXPECT_EQ ( crash_value , final_value ) ;
 }
 FlushIoTaskRunnerAndSpinThreads ( ) ;
 }