IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , DownloadRemoved ) {
 CreateDownload ( ) ;
 EXPECT_TRUE ( notification ( ) ) ;
 download_item ( ) -> Remove ( ) ;
 EXPECT_FALSE ( notification ( ) ) ;
 std : : vector < download : : DownloadItem * > downloads ;
 GetDownloadManager ( browser ( ) ) -> GetAllDownloads ( & downloads ) ;
 EXPECT_EQ ( 0u , downloads . size ( ) ) ;
 }