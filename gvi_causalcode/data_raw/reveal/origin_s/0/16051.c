IN_PROC_BROWSER_TEST_F ( UnloadTest , DISABLED_BrowserCloseInfiniteBeforeUnload ) {
 if ( base : : CommandLine : : ForCurrentProcess ( ) -> HasSwitch ( switches : : kSingleProcess ) ) return ;
 LoadUrlAndQuitBrowser ( INFINITE_BEFORE_UNLOAD_HTML , "infinitebeforeunload" ) ;
 }