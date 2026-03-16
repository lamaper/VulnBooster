IN_PROC_BROWSER_TEST_F ( ProfileBrowserTest , DISABLED_CreateOldProfileAsynchronous ) {
 base : : ScopedTempDir temp_dir ;
 ASSERT_TRUE ( temp_dir . CreateUniqueTempDir ( ) ) ;
 CreatePrefsFileInDirectory ( temp_dir . path ( ) ) ;
 MockProfileDelegate delegate ;
 EXPECT_CALL ( delegate , OnProfileCreated ( testing : : NotNull ( ) , true , false ) ) ;
 {
 content : : WindowedNotificationObserver observer ( chrome : : NOTIFICATION_PROFILE_CREATED , content : : NotificationService : : AllSources ( ) ) ;
 std : : unique_ptr < Profile > profile ( CreateProfile ( temp_dir . path ( ) , & delegate , Profile : : CREATE_MODE_ASYNCHRONOUS ) ) ;
 observer . Wait ( ) ;
 CheckChromeVersion ( profile . get ( ) , false ) ;
 }
 FlushIoTaskRunnerAndSpinThreads ( ) ;
 }