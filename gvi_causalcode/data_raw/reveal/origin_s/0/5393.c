IN_PROC_BROWSER_TEST_F ( UnloadTest , BrowserCloseInfiniteUnload ) {
 if ( base : : CommandLine : : ForCurrentProcess ( ) -> HasSwitch ( switches : : kSingleProcess ) ) return ;
 LoadUrlAndQuitBrowser ( INFINITE_UNLOAD_HTML , "infiniteunload" ) ;
 }