IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , CloseNotificationWhileDownloading ) {
 CreateDownload ( ) ;
 CloseNotification ( ) ;
 VerifyDownloadState ( download : : DownloadItem : : IN_PROGRESS ) ;
 CompleteTheDownload ( ) ;
 EXPECT_TRUE ( notification ( ) ) ;
 }