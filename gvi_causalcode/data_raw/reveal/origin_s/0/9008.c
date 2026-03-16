IN_PROC_BROWSER_TEST_F ( FastUnloadTest , PRE_WindowCloseFinishesUnload ) {
 NavigateToPage ( "no_listeners" ) ;
 NavigateToPageInNewTab ( "unload_sleep_before_cookie" ) ;
 EXPECT_EQ ( 2 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 EXPECT_EQ ( "" , GetCookies ( "no_listeners" ) ) ;
 content : : WindowedNotificationObserver window_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , content : : NotificationService : : AllSources ( ) ) ;
 chrome : : CloseWindow ( browser ( ) ) ;
 window_observer . Wait ( ) ;
 }