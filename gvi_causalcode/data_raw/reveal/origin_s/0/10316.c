IN_PROC_BROWSER_TEST_F ( UnloadTest , BrowserCloseInfiniteBeforeUnload ) {
 LoadUrlAndQuitBrowser ( INFINITE_BEFORE_UNLOAD_HTML , "infinitebeforeunload" ) ;
 }