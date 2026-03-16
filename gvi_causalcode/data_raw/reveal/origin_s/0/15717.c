IN_PROC_BROWSER_TEST_F ( FastUnloadTest , MAYBE_WindowCloseAfterBeforeUnloadCrash ) {
 if ( base : : CommandLine : : ForCurrentProcess ( ) -> HasSwitch ( switches : : kSingleProcess ) ) return ;
 NavigateToDataURL ( BEFORE_UNLOAD_HTML , "beforeunload" ) ;
 content : : WebContents * beforeunload_contents = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 content : : WindowedNotificationObserver window_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , content : : NotificationService : : AllSources ( ) ) ;
 chrome : : CloseWindow ( browser ( ) ) ;
 CrashTab ( beforeunload_contents ) ;
 window_observer . Wait ( ) ;
 }