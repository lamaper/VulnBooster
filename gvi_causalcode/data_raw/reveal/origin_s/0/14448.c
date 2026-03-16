IN_PROC_BROWSER_TEST_F ( SessionRestorePageLoadMetricsBrowserTest , RestoreForeignTab ) {
 sessions : : SerializedNavigationEntry nav = sessions : : SerializedNavigationEntryTestHelper : : CreateNavigation ( GetTestURL ( ) . spec ( ) , "one" ) ;
 sync_pb : : SessionTab sync_data ;
 sync_data . set_tab_visual_index ( 0 ) ;
 sync_data . set_current_navigation_index ( 1 ) ;
 sync_data . set_pinned ( false ) ;
 sync_data . add_navigation ( ) -> CopyFrom ( nav . ToSyncData ( ) ) ;
 sessions : : SessionTab tab ;
 tab . SetFromSyncData ( sync_data , base : : Time : : Now ( ) ) ;
 ASSERT_EQ ( 1 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 content : : WebContents * tab_contents = nullptr ;
 {
 SessionRestorePaintWaiter session_restore_paint_waiter ;
 tab_contents = SessionRestore : : RestoreForeignSessionTab ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , tab , WindowOpenDisposition : : CURRENT_TAB ) ;
 ASSERT_EQ ( 1 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 ASSERT_TRUE ( tab_contents ) ;
 ASSERT_EQ ( GetTestURL ( ) , tab_contents -> GetURL ( ) ) ;
 session_restore_paint_waiter . WaitForForegroundTabs ( 1 ) ;
 ExpectFirstPaintMetricsTotalCount ( 1 ) ;
 }
 {
 SessionRestorePaintWaiter session_restore_paint_waiter ;
 tab_contents = SessionRestore : : RestoreForeignSessionTab ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , tab , WindowOpenDisposition : : NEW_FOREGROUND_TAB ) ;
 ASSERT_EQ ( 2 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 ASSERT_EQ ( 1 , browser ( ) -> tab_strip_model ( ) -> active_index ( ) ) ;
 ASSERT_TRUE ( tab_contents ) ;
 ASSERT_EQ ( GetTestURL ( ) , tab_contents -> GetURL ( ) ) ;
 session_restore_paint_waiter . WaitForForegroundTabs ( 1 ) ;
 ExpectFirstPaintMetricsTotalCount ( 2 ) ;
 }
 {
 tab_contents = SessionRestore : : RestoreForeignSessionTab ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , tab , WindowOpenDisposition : : NEW_BACKGROUND_TAB ) ;
 ASSERT_EQ ( 3 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 ASSERT_EQ ( 1 , browser ( ) -> tab_strip_model ( ) -> active_index ( ) ) ;
 ASSERT_TRUE ( tab_contents ) ;
 ASSERT_EQ ( GetTestURL ( ) , tab_contents -> GetURL ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( WaitForTabsToLoad ( browser ( ) ) ) ;
 ExpectFirstPaintMetricsTotalCount ( 2 ) ;
 }
 }