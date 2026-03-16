IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , DISABLED_DiscardDangerousFile ) {
 GURL download_url ( embedded_test_server ( ) -> GetURL ( "/downloads/dangerous/dangerous.swf" ) ) ;
 content : : DownloadTestObserverTerminal download_terminal_observer ( GetDownloadManager ( browser ( ) ) , 1u , content : : DownloadTestObserver : : ON_DANGEROUS_DOWNLOAD_IGNORE ) ;
 CreateDownloadForBrowserAndURL ( browser ( ) , download_url ) ;
 base : : FilePath filename = download_item ( ) -> GetFileNameToReportUser ( ) ;
 EXPECT_EQ ( download : : DOWNLOAD_DANGER_TYPE_DANGEROUS_FILE , download_item ( ) -> GetDangerType ( ) ) ;
 EXPECT_TRUE ( download_item ( ) -> IsDangerous ( ) ) ;
 EXPECT_TRUE ( notification ( ) ) ;
 display_service_ -> SimulateClick ( NotificationHandler : : Type : : TRANSIENT , notification_id ( ) , 0 , base : : nullopt ) ;
 EXPECT_FALSE ( notification ( ) ) ;
 download_terminal_observer . WaitForFinished ( ) ;
 EXPECT_FALSE ( notification ( ) ) ;
 EXPECT_EQ ( 0u , GetDownloadNotifications ( ) . size ( ) ) ;
 std : : vector < download : : DownloadItem * > downloads ;
 GetDownloadManager ( browser ( ) ) -> GetAllDownloads ( & downloads ) ;
 EXPECT_EQ ( 0u , downloads . size ( ) ) ;
 EXPECT_FALSE ( base : : PathExists ( GetDownloadPath ( ) . Append ( filename . BaseName ( ) ) ) ) ;
 }