IN_PROC_BROWSER_TEST_F ( ProfileBrowserTest , CreateOldProfileSynchronous ) {
 base : : ScopedTempDir temp_dir ;
 ASSERT_TRUE ( temp_dir . CreateUniqueTempDir ( ) ) ;
 CreatePrefsFileInDirectory ( temp_dir . path ( ) ) ;
 MockProfileDelegate delegate ;
 EXPECT_CALL ( delegate , OnProfileCreated ( testing : : NotNull ( ) , true , false ) ) ;
 {
 std : : unique_ptr < Profile > profile ( CreateProfile ( temp_dir . path ( ) , & delegate , Profile : : CREATE_MODE_SYNCHRONOUS ) ) ;
 CheckChromeVersion ( profile . get ( ) , false ) ;
 }
 FlushIoTaskRunnerAndSpinThreads ( ) ;
 }