IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , IgnoreDownloads ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 base : : ScopedAllowBlockingForTesting allow_blocking ;
 base : : ScopedTempDir downloads_directory ;
 ASSERT_TRUE ( downloads_directory . CreateUniqueTempDir ( ) ) ;
 browser ( ) -> profile ( ) -> GetPrefs ( ) -> SetFilePath ( prefs : : kDownloadDefaultDirectory , downloads_directory . GetPath ( ) ) ;
 content : : DownloadTestObserverTerminal downloads_observer ( content : : BrowserContext : : GetDownloadManager ( browser ( ) -> profile ( ) ) , 1 , content : : DownloadTestObserver : : ON_DANGEROUS_DOWNLOAD_FAIL ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/download-test3.gif" ) ) ;
 downloads_observer . WaitForFinished ( ) ;
 NavigateToUntrackedUrl ( ) ;
 EXPECT_TRUE ( NoPageLoadMetricsRecorded ( ) ) << "Recorded metrics: " << GetRecordedPageLoadMetricNames ( ) ;
 }