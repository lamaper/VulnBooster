IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , DownloadFile ) {
 CreateDownload ( ) ;
 EXPECT_EQ ( l10n_util : : GetStringFUTF16 ( IDS_DOWNLOAD_STATUS_IN_PROGRESS_TITLE , download_item ( ) -> GetFileNameToReportUser ( ) . LossyDisplayName ( ) ) , notification ( ) -> title ( ) ) ;
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_PROGRESS , notification ( ) -> type ( ) ) ;
 EXPECT_TRUE ( notification ( ) ) ;
 VerifyUpdatePropagatesToNotification ( download_item ( ) ) ;
 CompleteTheDownload ( ) ;
 ASSERT_TRUE ( notification ( ) ) ;
 EXPECT_EQ ( l10n_util : : GetStringUTF16 ( IDS_DOWNLOAD_STATUS_COMPLETE_TITLE ) , notification ( ) -> title ( ) ) ;
 EXPECT_EQ ( download_item ( ) -> GetFileNameToReportUser ( ) . LossyDisplayName ( ) , notification ( ) -> message ( ) ) ;
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_BASE_FORMAT , notification ( ) -> type ( ) ) ;
 ASSERT_EQ ( 1u , GetDownloadNotifications ( ) . size ( ) ) ;
 EXPECT_FALSE ( GetDownloadManagerDelegate ( ) -> opened ( ) ) ;
 display_service_ -> SimulateClick ( NotificationHandler : : Type : : TRANSIENT , notification_id ( ) , base : : nullopt , base : : nullopt ) ;
 EXPECT_TRUE ( GetDownloadManagerDelegate ( ) -> opened ( ) ) ;
 EXPECT_FALSE ( GetNotification ( notification_id ( ) ) ) ;
 }