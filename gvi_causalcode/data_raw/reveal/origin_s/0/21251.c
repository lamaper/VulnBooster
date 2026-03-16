IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , CancelDownload ) {
 CreateDownload ( ) ;
 display_service_ -> SimulateClick ( NotificationHandler : : Type : : TRANSIENT , notification_id ( ) , 1 , base : : nullopt ) ;
 EXPECT_FALSE ( notification ( ) ) ;
 EXPECT_EQ ( 0u , GetDownloadNotifications ( ) . size ( ) ) ;
 std : : vector < download : : DownloadItem * > downloads ;
 GetDownloadManager ( browser ( ) ) -> GetAllDownloads ( & downloads ) ;
 ASSERT_EQ ( 1u , downloads . size ( ) ) ;
 EXPECT_EQ ( download : : DownloadItem : : CANCELLED , downloads [ 0 ] -> GetState ( ) ) ;
 }