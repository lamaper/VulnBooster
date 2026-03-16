IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , TestWithDangerousUrlDownload ) {
 std : : unique_ptr < TestDownloadManagerDelegate > test_delegate ( new TestDownloadManagerDelegate ( browser ( ) -> profile ( ) ) ) ;
 DownloadCoreServiceFactory : : GetForBrowserContext ( browser ( ) -> profile ( ) ) -> SetDownloadManagerDelegateForTesting ( std : : move ( test_delegate ) ) ;
 GURL download_url ( embedded_test_server ( ) -> GetURL ( "/downloads/dangerous/dangerous.swf" ) ) ;
 content : : DownloadTestObserverInterrupted observer ( content : : BrowserContext : : GetDownloadManager ( browser ( ) -> profile ( ) ) , 1 , content : : DownloadTestObserver : : ON_DANGEROUS_DOWNLOAD_QUIT ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , GURL ( download_url ) , WindowOpenDisposition : : NEW_BACKGROUND_TAB , ui_test_utils : : BROWSER_TEST_NONE ) ;
 observer . WaitForFinished ( ) ;
 EXPECT_EQ ( 1 , content : : BrowserContext : : GetDownloadManager ( browser ( ) -> profile ( ) ) -> InProgressCount ( ) ) ;
 EXPECT_EQ ( 0 , content : : BrowserContext : : GetDownloadManager ( browser ( ) -> profile ( ) ) -> NonMaliciousInProgressCount ( ) ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 1 ) ;
 TestBrowserCloseManager : : AttemptClose ( TestBrowserCloseManager : : NO_USER_CHOICE ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 }