IN_PROC_BROWSER_TEST_F ( UnloadTest , BrowserCloseBeforeUnloadCancel ) {
 NavigateToDataURL ( BEFORE_UNLOAD_HTML , "beforeunload" ) ;
 chrome : : CloseWindow ( browser ( ) ) ;
 base : : string16 expected_title = base : : ASCIIToUTF16 ( "cancelled" ) ;
 content : : TitleWatcher title_watcher ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , expected_title ) ;
 ClickModalDialogButton ( false ) ;
 ASSERT_EQ ( expected_title , title_watcher . WaitAndGetTitle ( ) ) ;
 content : : WindowedNotificationObserver window_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , content : : NotificationService : : AllSources ( ) ) ;
 chrome : : CloseWindow ( browser ( ) ) ;
 ClickModalDialogButton ( true ) ;
 window_observer . Wait ( ) ;
 }