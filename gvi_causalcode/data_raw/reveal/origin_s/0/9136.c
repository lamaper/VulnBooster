IN_PROC_BROWSER_TEST_F ( UnloadTest , BrowserCloseWithInnerFocusedFrame ) {
 NavigateToDataURL ( INNER_FRAME_WITH_FOCUS_HTML , "innerframewithfocus" ) ;
 content : : WindowedNotificationObserver window_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , content : : NotificationService : : AllSources ( ) ) ;
 chrome : : CloseWindow ( browser ( ) ) ;
 ClickModalDialogButton ( true ) ;
 window_observer . Wait ( ) ;
 }