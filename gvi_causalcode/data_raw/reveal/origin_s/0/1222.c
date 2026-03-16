IN_PROC_BROWSER_TEST_F ( DownloadNotificationTest , InterruptDownload ) {
 CreateDownload ( ) ;
 InterruptTheDownload ( ) ;
 EXPECT_EQ ( 1u , GetDownloadNotifications ( ) . size ( ) ) ;
 ASSERT_TRUE ( notification ( ) ) ;
 EXPECT_EQ ( l10n_util : : GetStringFUTF16 ( IDS_DOWNLOAD_STATUS_DOWNLOAD_FAILED_TITLE , download_item ( ) -> GetFileNameToReportUser ( ) . LossyDisplayName ( ) ) , notification ( ) -> title ( ) ) ;
 EXPECT_NE ( notification ( ) -> message ( ) . find ( l10n_util : : GetStringFUTF16 ( IDS_DOWNLOAD_STATUS_INTERRUPTED , l10n_util : : GetStringUTF16 ( IDS_DOWNLOAD_INTERRUPTED_DESCRIPTION_NETWORK_ERROR ) ) ) , std : : string : : npos ) ;
 EXPECT_EQ ( message_center : : NOTIFICATION_TYPE_BASE_FORMAT , notification ( ) -> type ( ) ) ;
 }