IN_PROC_BROWSER_TEST_F ( UnloadTest , BrowserListForceCloseAfterNormalClose ) {
 NavigateToDataURL ( BEFORE_UNLOAD_HTML , "beforeunload" ) ;
 content : : WindowedNotificationObserver window_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , content : : NotificationService : : AllSources ( ) ) ;
 UnloadResults unload_results ;
 BrowserList : : CloseAllBrowsersWithProfile ( browser ( ) -> profile ( ) , base : : Bind ( & UnloadResults : : AddSuccess , base : : Unretained ( & unload_results ) ) , base : : Bind ( & UnloadResults : : AddAbort , base : : Unretained ( & unload_results ) ) , false ) ;
 BrowserList : : CloseAllBrowsersWithProfile ( browser ( ) -> profile ( ) , base : : Bind ( & UnloadResults : : AddSuccess , base : : Unretained ( & unload_results ) ) , base : : Bind ( & UnloadResults : : AddAbort , base : : Unretained ( & unload_results ) ) , true ) ;
 window_observer . Wait ( ) ;
 EXPECT_EQ ( 1 , unload_results . get_successes ( ) ) ;
 EXPECT_EQ ( 0 , unload_results . get_aborts ( ) ) ;
 }