IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , InterruptDownloadAfterClosingNotification ) {
 CreateDownload ( ) ;
 CloseNotification ( ) ;
 std : : vector < download : : DownloadItem * > downloads ;
 content : : DownloadManager * download_manager = GetDownloadManager ( browser ( ) ) ;
 download_manager -> GetAllDownloads ( & downloads ) ;
 EXPECT_EQ ( 1u , downloads . size ( ) ) ;
 EXPECT_EQ ( download : : DownloadItem : : IN_PROGRESS , downloads [ 0 ] -> GetState ( ) ) ;
 content : : DownloadTestObserverInterrupted download_terminal_observer ( download_manager , 1u , content : : DownloadTestObserver : : ON_DANGEROUS_DOWNLOAD_FAIL ) ;
 InterruptTheDownload ( ) ;
 EXPECT_EQ ( 1u , GetDownloadNotifications ( ) . size ( ) ) ;
 ASSERT_TRUE ( notification ( ) ) ;
 }