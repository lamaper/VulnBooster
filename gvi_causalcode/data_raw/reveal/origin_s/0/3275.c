IN_PROC_BROWSER_TEST_F ( MultiProfileDownloadNotificationTest , DownloadMultipleFiles ) {
 AddAllUsers ( ) ;
 GURL url ( net : : URLRequestSlowDownloadJob : : kUnknownSizeUrl ) ;
 Profile * profile1 = GetProfileByIndex ( 1 ) ;
 Profile * profile2 = GetProfileByIndex ( 2 ) ;
 Browser * browser1 = CreateBrowser ( profile1 ) ;
 Browser * browser2 = CreateBrowser ( profile2 ) ;
 EXPECT_NE ( browser1 , browser2 ) ;
 display_service1_ = std : : make_unique < NotificationDisplayServiceTester > ( profile1 ) ;
 display_service2_ = std : : make_unique < NotificationDisplayServiceTester > ( profile2 ) ;
 ui_test_utils : : NavigateToURL ( browser1 , url ) ;
 WaitForDownloadNotificationForDisplayService ( display_service1_ . get ( ) ) ;
 std : : vector < download : : DownloadItem * > downloads ;
 GetDownloadManager ( browser1 ) -> GetAllDownloads ( & downloads ) ;
 EXPECT_EQ ( 1u , downloads . size ( ) ) ;
 download : : DownloadItem * download1 = downloads [ 0 ] ;
 auto notifications1 = display_service1_ -> GetDisplayedNotificationsForType ( NotificationHandler : : Type : : TRANSIENT ) ;
 ASSERT_EQ ( 1u , notifications1 . size ( ) ) ;
 std : : string notification_id_user1 = notifications1 [ 0 ] . id ( ) ;
 EXPECT_FALSE ( notification_id_user1 . empty ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser2 , url ) ;
 WaitForDownloadNotificationForDisplayService ( display_service2_ . get ( ) ) ;
 auto notifications2 = display_service2_ -> GetDisplayedNotificationsForType ( NotificationHandler : : Type : : TRANSIENT ) ;
 ASSERT_EQ ( 1u , notifications2 . size ( ) ) ;
 std : : string notification_id_user2 = notifications2 [ 0 ] . id ( ) ;
 EXPECT_FALSE ( notification_id_user2 . empty ( ) ) ;
 downloads . clear ( ) ;
 GetDownloadManager ( browser2 ) -> GetAllDownloads ( & downloads ) ;
 ASSERT_EQ ( 1u , downloads . size ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser2 , url ) ;
 WaitForDownloadNotificationForDisplayService ( display_service2_ . get ( ) ) ;
 notifications2 = display_service2_ -> GetDisplayedNotificationsForType ( NotificationHandler : : Type : : TRANSIENT ) ;
 ASSERT_EQ ( 2u , notifications2 . size ( ) ) ;
 downloads . clear ( ) ;
 GetDownloadManager ( browser2 ) -> GetAllDownloads ( & downloads ) ;
 ASSERT_EQ ( 2u , downloads . size ( ) ) ;
 download : : DownloadItem * download2 = downloads [ 0 ] ;
 download : : DownloadItem * download3 = downloads [ 1 ] ;
 EXPECT_NE ( download1 , download2 ) ;
 EXPECT_NE ( download1 , download3 ) ;
 EXPECT_NE ( download2 , download3 ) ;
 downloads . clear ( ) ;
 GetDownloadManager ( browser1 ) -> GetAllDownloads ( & downloads ) ;
 ASSERT_EQ ( 1u , downloads . size ( ) ) ;
 EXPECT_EQ ( download1 , downloads [ 0 ] ) ;
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_PROGRESS , display_service1_ -> GetNotification ( notification_id_user1 ) -> type ( ) ) ;
 EXPECT_EQ ( - 1 , display_service1_ -> GetNotification ( notification_id_user1 ) -> progress ( ) ) ;
 notifications2 = display_service2_ -> GetDisplayedNotificationsForType ( NotificationHandler : : Type : : TRANSIENT ) ;
 EXPECT_EQ ( 2u , notifications2 . size ( ) ) ;
 for ( const auto & notification : notifications2 ) {
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_PROGRESS , notification . type ( ) ) ;
 EXPECT_EQ ( - 1 , notification . progress ( ) ) ;
 }
 content : : DownloadTestObserverTerminal download_terminal_observer ( GetDownloadManager ( browser1 ) , 1u , content : : DownloadTestObserver : : ON_DANGEROUS_DOWNLOAD_FAIL ) ;
 content : : DownloadTestObserverTerminal download_terminal_observer2 ( GetDownloadManager ( browser2 ) , 2u , content : : DownloadTestObserver : : ON_DANGEROUS_DOWNLOAD_FAIL ) ;
 ui_test_utils : : NavigateToURL ( browser1 , GURL ( net : : URLRequestSlowDownloadJob : : kFinishDownloadUrl ) ) ;
 ui_test_utils : : NavigateToURL ( browser2 , GURL ( net : : URLRequestSlowDownloadJob : : kFinishDownloadUrl ) ) ;
 download_terminal_observer . WaitForFinished ( ) ;
 download_terminal_observer2 . WaitForFinished ( ) ;
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_BASE_FORMAT , display_service1_ -> GetNotification ( notification_id_user1 ) -> type ( ) ) ;
 notifications2 = display_service2_ -> GetDisplayedNotificationsForType ( NotificationHandler : : Type : : TRANSIENT ) ;
 EXPECT_EQ ( 2u , notifications2 . size ( ) ) ;
 for ( const auto & notification : notifications2 ) {
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_BASE_FORMAT , notification . type ( ) ) ;
 }
 }