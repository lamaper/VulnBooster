IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , DISABLED_DownloadImageFile ) {
 GURL download_url ( embedded_test_server ( ) -> GetURL ( "/downloads/image-octet-stream.png" ) ) ;
 content : : DownloadTestObserverTerminal download_terminal_observer ( GetDownloadManager ( browser ( ) ) , 1u , content : : DownloadTestObserver : : ON_DANGEROUS_DOWNLOAD_IGNORE ) ;
 CreateDownloadForBrowserAndURL ( browser ( ) , download_url ) ;
 download_terminal_observer . WaitForFinished ( ) ;
 WaitForDownloadNotification ( ) ;
 EXPECT_FALSE ( notification ( ) -> image ( ) . IsEmpty ( ) ) ;
 }