IN_PROC_BROWSER_TEST_F ( FastUnloadTest , PRE_ClosingLastTabFinishesUnload ) {
 NavigateToPage ( "unload_sleep_before_cookie" ) ;
 EXPECT_EQ ( 1 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 EXPECT_EQ ( "" , GetCookies ( "unload_sleep_before_cookie" ) ) ;
 content : : WindowedNotificationObserver window_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , content : : NotificationService : : AllSources ( ) ) ;
 chrome : : CloseTab ( browser ( ) ) ;
 window_observer . Wait ( ) ;
 }