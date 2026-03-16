IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , DownloadMultipleFilesOneByOne ) {
 CreateDownload ( ) ;
 download : : DownloadItem * first_download_item = download_item ( ) ;
 std : : string first_notification_id = notification_id ( ) ;
 CompleteTheDownload ( ) ;
 EXPECT_EQ ( download : : DownloadItem : : COMPLETE , first_download_item -> GetState ( ) ) ;
 EXPECT_TRUE ( notification ( ) ) ;
 GURL url ( net : : URLRequestSlowDownloadJob : : kKnownSizeUrl ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url ) ;
 WaitForDownloadNotification ( ) ;
 auto notifications = GetDownloadNotifications ( ) ;
 ASSERT_EQ ( 2u , notifications . size ( ) ) ;
 std : : string second_notification_id = notifications [ ( notifications [ 0 ] . id ( ) == notification_id ( ) ? 1 : 0 ) ] . id ( ) ;
 EXPECT_FALSE ( second_notification_id . empty ( ) ) ;
 ASSERT_TRUE ( GetNotification ( second_notification_id ) ) ;
 std : : vector < download : : DownloadItem * > downloads ;
 GetDownloadManager ( browser ( ) ) -> GetAllDownloads ( & downloads ) ;
 EXPECT_EQ ( 2u , downloads . size ( ) ) ;
 EXPECT_TRUE ( first_download_item == downloads [ 0 ] || first_download_item == downloads [ 1 ] ) ;
 download : : DownloadItem * second_download_item = downloads [ first_download_item == downloads [ 0 ] ? 1 : 0 ] ;
 EXPECT_EQ ( download : : DownloadItem : : IN_PROGRESS , second_download_item -> GetState ( ) ) ;
 CompleteTheDownload ( ) ;
 EXPECT_EQ ( 2u , GetDownloadNotifications ( ) . size ( ) ) ;
 }