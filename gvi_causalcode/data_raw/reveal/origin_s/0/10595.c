IN_PROC_BROWSER_TEST_F ( SessionRestorePageLoadMetricsBrowserTest , RestoreForeignSession ) {
 Profile * profile = browser ( ) -> profile ( ) ;
 sessions : : SerializedNavigationEntry nav1 = sessions : : SerializedNavigationEntryTestHelper : : CreateNavigation ( GetTestURL ( ) . spec ( ) , "one" ) ;
 sessions : : SerializedNavigationEntry nav2 = sessions : : SerializedNavigationEntryTestHelper : : CreateNavigation ( GetTestURL2 ( ) . spec ( ) , "two" ) ;
 std : : vector < const sessions : : SessionWindow * > session ;
 sessions : : SessionWindow window ;
 auto tab1 = std : : make_unique < sessions : : SessionTab > ( ) ;
 {
 sync_pb : : SessionTab sync_data ;
 sync_data . set_tab_visual_index ( 0 ) ;
 sync_data . set_current_navigation_index ( 0 ) ;
 sync_data . set_pinned ( true ) ;
 sync_data . add_navigation ( ) -> CopyFrom ( nav1 . ToSyncData ( ) ) ;
 tab1 -> SetFromSyncData ( sync_data , base : : Time : : Now ( ) ) ;
 }
 window . tabs . push_back ( std : : move ( tab1 ) ) ;
 auto tab2 = std : : make_unique < sessions : : SessionTab > ( ) ;
 {
 sync_pb : : SessionTab sync_data ;
 sync_data . set_tab_visual_index ( 1 ) ;
 sync_data . set_current_navigation_index ( 0 ) ;
 sync_data . set_pinned ( false ) ;
 sync_data . add_navigation ( ) -> CopyFrom ( nav2 . ToSyncData ( ) ) ;
 tab2 -> SetFromSyncData ( sync_data , base : : Time : : Now ( ) ) ;
 }
 window . tabs . push_back ( std : : move ( tab2 ) ) ;
 session . push_back ( static_cast < const sessions : : SessionWindow * > ( & window ) ) ;
 ui_test_utils : : BrowserAddedObserver window_observer ;
 SessionRestorePaintWaiter session_restore_paint_waiter ;
 SessionRestore : : RestoreForeignSessionWindows ( profile , session . begin ( ) , session . end ( ) ) ;
 Browser * new_browser = window_observer . WaitForSingleNewBrowser ( ) ;
 ASSERT_TRUE ( new_browser ) ;
 ASSERT_EQ ( 2 , new_browser -> tab_strip_model ( ) -> count ( ) ) ;
 session_restore_paint_waiter . WaitForForegroundTabs ( 1 ) ;
 ASSERT_NO_FATAL_FAILURE ( WaitForTabsToLoad ( new_browser ) ) ;
 ExpectFirstPaintMetricsTotalCount ( 1 ) ;
 }