IN_PROC_BROWSER_TEST_F ( UnloadTest , BrowserCloseBeforeUnloadOK ) {
 NavigateToDataURL ( BEFORE_UNLOAD_HTML , "beforeunload" ) ;
 content : : WindowedNotificationObserver window_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , content : : NotificationService : : AllSources ( ) ) ;
 chrome : : CloseWindow ( browser ( ) ) ;
 ClickModalDialogButton ( true ) ;
 window_observer . Wait ( ) ;
 }