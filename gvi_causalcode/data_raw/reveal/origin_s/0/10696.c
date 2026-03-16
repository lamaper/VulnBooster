IN_PROC_BROWSER_TEST_F ( FastUnloadTest , DISABLED_WindowCloseAfterUnloadCrash ) {
 NavigateToPage ( "no_listeners" ) ;
 NavigateToPageInNewTab ( "unload_sets_cookie" ) ;
 content : : WebContents * unload_contents = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 EXPECT_EQ ( "" , GetCookies ( "no_listeners" ) ) ;
 {
 base : : RunLoop run_loop ;
 FastTabCloseTabStripModelObserver observer ( browser ( ) -> tab_strip_model ( ) , & run_loop ) ;
 chrome : : CloseTab ( browser ( ) ) ;
 run_loop . Run ( ) ;
 }
 CheckTitle ( "no_listeners" ) ;
 EXPECT_EQ ( 1 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 CrashTab ( unload_contents ) ;
 CheckTitle ( "no_listeners" ) ;
 EXPECT_EQ ( 1 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 content : : WindowedNotificationObserver window_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , content : : NotificationService : : AllSources ( ) ) ;
 chrome : : CloseWindow ( browser ( ) ) ;
 window_observer . Wait ( ) ;
 }