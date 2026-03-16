IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , IncognitoDownloadFile ) {
 PrepareIncognitoBrowser ( ) ;
 CreateDownloadForBrowserAndURL ( incognito_browser ( ) , GURL ( net : : URLRequestSlowDownloadJob : : kKnownSizeUrl ) ) ;
 EXPECT_EQ ( l10n_util : : GetStringFUTF16 ( IDS_DOWNLOAD_STATUS_IN_PROGRESS_TITLE , download_item ( ) -> GetFileNameToReportUser ( ) . LossyDisplayName ( ) ) , notification ( ) -> title ( ) ) ;
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_PROGRESS , notification ( ) -> type ( ) ) ;
 EXPECT_TRUE ( content : : DownloadItemUtils : : GetBrowserContext ( download_item ( ) ) -> IsOffTheRecord ( ) ) ;
 content : : DownloadTestObserverTerminal download_terminal_observer ( GetDownloadManager ( incognito_browser ( ) ) , 1 , content : : DownloadTestObserver : : ON_DANGEROUS_DOWNLOAD_FAIL ) ;
 ui_test_utils : : NavigateToURL ( incognito_browser ( ) , GURL ( net : : URLRequestSlowDownloadJob : : kFinishDownloadUrl ) ) ;
 download_terminal_observer . WaitForFinished ( ) ;
 EXPECT_EQ ( l10n_util : : GetStringUTF16 ( IDS_DOWNLOAD_STATUS_COMPLETE_TITLE ) , notification ( ) -> title ( ) ) ;
 EXPECT_EQ ( download_item ( ) -> GetFileNameToReportUser ( ) . LossyDisplayName ( ) , notification ( ) -> message ( ) ) ;
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_BASE_FORMAT , notification ( ) -> type ( ) ) ;
 EXPECT_TRUE ( incognito_display_service_ -> GetNotification ( notification_id ( ) ) ) ;
 EXPECT_FALSE ( GetIncognitoDownloadManagerDelegate ( ) -> opened ( ) ) ;
 incognito_display_service_ -> SimulateClick ( NotificationHandler : : Type : : TRANSIENT , notification_id ( ) , base : : nullopt , base : : nullopt ) ;
 EXPECT_TRUE ( GetIncognitoDownloadManagerDelegate ( ) -> opened ( ) ) ;
 EXPECT_FALSE ( GetDownloadManagerDelegate ( ) -> opened ( ) ) ;
 EXPECT_FALSE ( incognito_display_service_ -> GetNotification ( notification_id ( ) ) ) ;
 chrome : : CloseWindow ( incognito_browser ( ) ) ;
 }