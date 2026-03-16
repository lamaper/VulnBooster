IN_PROC_BROWSER_TEST_F ( ProfileBrowserTest , DISABLED_ProfileReadmeCreated ) {
 base : : ScopedTempDir temp_dir ;
 ASSERT_TRUE ( temp_dir . CreateUniqueTempDir ( ) ) ;
 MockProfileDelegate delegate ;
 EXPECT_CALL ( delegate , OnProfileCreated ( testing : : NotNull ( ) , true , true ) ) ;
 {
 content : : WindowedNotificationObserver observer ( chrome : : NOTIFICATION_PROFILE_CREATED , content : : NotificationService : : AllSources ( ) ) ;
 std : : unique_ptr < Profile > profile ( CreateProfile ( temp_dir . path ( ) , & delegate , Profile : : CREATE_MODE_ASYNCHRONOUS ) ) ;
 observer . Wait ( ) ;
 EXPECT_TRUE ( base : : PathExists ( temp_dir . path ( ) . Append ( chrome : : kReadmeFilename ) ) ) ;
 }
 FlushIoTaskRunnerAndSpinThreads ( ) ;
 }