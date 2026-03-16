IN_PROC_BROWSER_TEST_F ( UnloadTest , BrowserCloseTabWhenOtherTabHasListener ) {
 NavigateToDataURL ( CLOSE_TAB_WHEN_OTHER_TAB_HAS_LISTENER , "only_one_unload" ) ;
 content : : WindowedNotificationObserver observer ( chrome : : NOTIFICATION_TAB_ADDED , content : : NotificationService : : AllSources ( ) ) ;
 content : : WindowedNotificationObserver load_stop_observer ( content : : NOTIFICATION_LOAD_STOP , content : : NotificationService : : AllSources ( ) ) ;
 content : : SimulateMouseClick ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , 0 , blink : : WebMouseEvent : : Button : : Left ) ;
 observer . Wait ( ) ;
 load_stop_observer . Wait ( ) ;
 CheckTitle ( "popup" ) ;
 content : : WebContentsDestroyedWatcher destroyed_watcher ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ) ;
 chrome : : CloseTab ( browser ( ) ) ;
 destroyed_watcher . Wait ( ) ;
 CheckTitle ( "only_one_unload" ) ;
 }