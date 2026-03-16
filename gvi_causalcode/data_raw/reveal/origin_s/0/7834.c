IN_PROC_BROWSER_TEST_F ( UnloadTest , BrowserListCloseBeforeUnloadCancel ) {
 NavigateToDataURL ( BEFORE_UNLOAD_HTML , "beforeunload" ) ;
 UnloadResults unload_results ;
 BrowserList : : CloseAllBrowsersWithProfile ( browser ( ) -> profile ( ) , base : : Bind ( & UnloadResults : : AddSuccess , base : : Unretained ( & unload_results ) ) , base : : Bind ( & UnloadResults : : AddAbort , base : : Unretained ( & unload_results ) ) , false ) ;
 base : : string16 expected_title = base : : ASCIIToUTF16 ( "cancelled" ) ;
 content : : TitleWatcher title_watcher ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , expected_title ) ;
 ClickModalDialogButton ( false ) ;
 ASSERT_EQ ( expected_title , title_watcher . WaitAndGetTitle ( ) ) ;
 EXPECT_EQ ( 0 , unload_results . get_successes ( ) ) ;
 EXPECT_EQ ( 1 , unload_results . get_aborts ( ) ) ;
 content : : WindowedNotificationObserver window_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , content : : NotificationService : : AllSources ( ) ) ;
 chrome : : CloseWindow ( browser ( ) ) ;
 ClickModalDialogButton ( true ) ;
 window_observer . Wait ( ) ;
 }