IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , DownloadCancelledByUserExternally ) {
 CreateDownload ( ) ;
 download_item ( ) -> Cancel ( true ) ;
 EXPECT_FALSE ( notification ( ) ) ;
 EXPECT_EQ ( 0u , GetDownloadNotifications ( ) . size ( ) ) ;
 std : : vector < download : : DownloadItem * > downloads ;
 GetDownloadManager ( browser ( ) ) -> GetAllDownloads ( & downloads ) ;
 EXPECT_EQ ( 1u , downloads . size ( ) ) ;
 EXPECT_EQ ( download : : DownloadItem : : CANCELLED , downloads [ 0 ] -> GetState ( ) ) ;
 }