IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , CloseNotificationAfterDownload ) {
 CreateDownload ( ) ;
 CompleteTheDownload ( ) ;
 CloseNotification ( ) ;
 VerifyDownloadState ( download : : DownloadItem : : COMPLETE ) ;
 }