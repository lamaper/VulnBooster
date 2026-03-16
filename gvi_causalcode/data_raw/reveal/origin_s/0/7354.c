IN_PROC_BROWSER_TEST_F ( FastUnloadTest , MAYBE_UnloadHidden ) {
 NavigateToPage ( "no_listeners" ) ;
 NavigateToPageInNewTab ( "unload_sets_cookie" ) ;
 EXPECT_EQ ( "" , GetCookies ( "no_listeners" ) ) ;
 content : : WebContentsDestroyedWatcher destroyed_watcher ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ) ;
 {
 base : : RunLoop run_loop ;
 FastTabCloseTabStripModelObserver observer ( browser ( ) -> tab_strip_model ( ) , & run_loop ) ;
 chrome : : CloseTab ( browser ( ) ) ;
 run_loop . Run ( ) ;
 }
 CheckTitle ( "no_listeners" ) ;
 EXPECT_EQ ( 1 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 destroyed_watcher . Wait ( ) ;
 EXPECT_EQ ( "unloaded=ohyeah" , GetCookies ( "no_listeners" ) ) ;
 }