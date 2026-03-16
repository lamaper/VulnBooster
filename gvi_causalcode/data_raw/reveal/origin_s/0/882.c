IN_PROC_BROWSER_TEST_F ( BlockedAppApiTest , MAYBE_OpenAppFromIframe ) {
 const Extension * app = LoadExtension ( test_data_dir_ . AppendASCII ( "app_process" ) ) ;
 ASSERT_TRUE ( app ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , GetTestBaseURL ( "app_process" ) . Resolve ( "path3/container.html" ) ) ;
 WebContents * tab = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 PopupBlockerTabHelper * popup_blocker_tab_helper = PopupBlockerTabHelper : : FromWebContents ( tab ) ;
 if ( ! popup_blocker_tab_helper -> GetBlockedPopupsCount ( ) ) {
 content : : WindowedNotificationObserver observer ( chrome : : NOTIFICATION_WEB_CONTENT_SETTINGS_CHANGED , content : : NotificationService : : AllSources ( ) ) ;
 observer . Wait ( ) ;
 }
 EXPECT_EQ ( 1u , popup_blocker_tab_helper -> GetBlockedPopupsCount ( ) ) ;
 }