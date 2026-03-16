IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , DownloadMultipleFiles ) {
 GURL url1 ( net : : URLRequestSlowDownloadJob : : kUnknownSizeUrl ) ;
 GURL url2 ( net : : URLRequestSlowDownloadJob : : kKnownSizeUrl ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url1 ) ;
 WaitForDownloadNotification ( ) ;
 auto notifications = GetDownloadNotifications ( ) ;
 ASSERT_EQ ( 1u , notifications . size ( ) ) ;
 std : : string notification_id1 = notifications [ 0 ] . id ( ) ;
 EXPECT_FALSE ( notification_id1 . empty ( ) ) ;
 std : : vector < download : : DownloadItem * > downloads ;
 GetDownloadManager ( browser ( ) ) -> GetAllDownloads ( & downloads ) ;
 ASSERT_EQ ( 1u , downloads . size ( ) ) ;
 download : : DownloadItem * download1 = downloads [ 0 ] ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url2 ) ;
 WaitForDownloadNotification ( ) ;
 downloads . clear ( ) ;
 GetDownloadManager ( browser ( ) ) -> GetAllDownloads ( & downloads ) ;
 ASSERT_EQ ( 2u , downloads . size ( ) ) ;
 download : : DownloadItem * download2 ;
 if ( download1 == downloads [ 0 ] ) download2 = downloads [ 1 ] ;
 else if ( download1 == downloads [ 1 ] ) download2 = downloads [ 0 ] ;
 else NOTREACHED ( ) ;
 EXPECT_NE ( download1 , download2 ) ;
 notifications = GetDownloadNotifications ( ) ;
 EXPECT_EQ ( 2u , notifications . size ( ) ) ;
 std : : string notification_id2 ;
 for ( const auto & notification : notifications ) {
 if ( notification . id ( ) == notification_id1 ) continue ;
 notification_id2 = notification . id ( ) ;
 }
 EXPECT_FALSE ( notification_id2 . empty ( ) ) ;
 const int in_progress_priority1 = GetNotification ( notification_id1 ) -> priority ( ) ;
 const int in_progress_priority2 = GetNotification ( notification_id2 ) -> priority ( ) ;
 EXPECT_EQ ( message_center : : LOW_PRIORITY , in_progress_priority1 ) ;
 EXPECT_EQ ( message_center : : DEFAULT_PRIORITY , in_progress_priority2 ) ;
 VerifyUpdatePropagatesToNotification ( download1 ) ;
 VerifyUpdatePropagatesToNotification ( download2 ) ;
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_PROGRESS , GetNotification ( notification_id1 ) -> type ( ) ) ;
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_PROGRESS , GetNotification ( notification_id2 ) -> type ( ) ) ;
 CompleteTheDownload ( 2 ) ;
 notifications = GetDownloadNotifications ( ) ;
 EXPECT_EQ ( 2u , notifications . size ( ) ) ;
 ASSERT_TRUE ( GetNotification ( notification_id1 ) ) ;
 ASSERT_TRUE ( GetNotification ( notification_id2 ) ) ;
 EXPECT_GT ( GetNotification ( notification_id1 ) -> priority ( ) , in_progress_priority1 ) ;
 EXPECT_GT ( GetNotification ( notification_id2 ) -> priority ( ) , in_progress_priority2 ) ;
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_BASE_FORMAT , GetNotification ( notification_id1 ) -> type ( ) ) ;
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_BASE_FORMAT , GetNotification ( notification_id2 ) -> type ( ) ) ;
 }