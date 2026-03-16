IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , DISABLED_DownloadDangerousFile ) {
 GURL download_url ( embedded_test_server ( ) -> GetURL ( "/downloads/dangerous/dangerous.swf" ) ) ;
 content : : DownloadTestObserverTerminal download_terminal_observer ( GetDownloadManager ( browser ( ) ) , 1u , content : : DownloadTestObserver : : ON_DANGEROUS_DOWNLOAD_IGNORE ) ;
 CreateDownloadForBrowserAndURL ( browser ( ) , download_url ) ;
 base : : FilePath filename = download_item ( ) -> GetFileNameToReportUser ( ) ;
 EXPECT_EQ ( download : : DOWNLOAD_DANGER_TYPE_DANGEROUS_FILE , download_item ( ) -> GetDangerType ( ) ) ;
 EXPECT_TRUE ( download_item ( ) -> IsDangerous ( ) ) ;
 display_service_ -> SimulateClick ( NotificationHandler : : Type : : TRANSIENT , notification_id ( ) , 1 , base : : nullopt ) ;
 EXPECT_TRUE ( notification ( ) ) ;
 EXPECT_EQ ( download : : DOWNLOAD_DANGER_TYPE_USER_VALIDATED , download_item ( ) -> GetDangerType ( ) ) ;
 EXPECT_FALSE ( download_item ( ) -> IsDangerous ( ) ) ;
 download_terminal_observer . WaitForFinished ( ) ;
 EXPECT_FALSE ( download_item ( ) -> IsDangerous ( ) ) ;
 EXPECT_EQ ( download : : DownloadItem : : COMPLETE , download_item ( ) -> GetState ( ) ) ;
 EXPECT_TRUE ( base : : PathExists ( GetDownloadPath ( ) . Append ( filename . BaseName ( ) ) ) ) ;
 }