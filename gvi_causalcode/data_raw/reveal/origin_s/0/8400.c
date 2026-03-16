IN_PROC_BROWSER_TEST_F ( ProfileBrowserTest , CreateNewProfileSynchronous ) {
 base : : ScopedTempDir temp_dir ;
 ASSERT_TRUE ( temp_dir . CreateUniqueTempDir ( ) ) ;
 MockProfileDelegate delegate ;
 EXPECT_CALL ( delegate , OnProfileCreated ( testing : : NotNull ( ) , true , true ) ) ;
 {
 std : : unique_ptr < Profile > profile ( CreateProfile ( temp_dir . path ( ) , & delegate , Profile : : CREATE_MODE_SYNCHRONOUS ) ) ;
 CheckChromeVersion ( profile . get ( ) , true ) ;
 }
 FlushIoTaskRunnerAndSpinThreads ( ) ;
 }