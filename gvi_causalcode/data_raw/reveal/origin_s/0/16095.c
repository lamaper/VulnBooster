IN_PROC_BROWSER_TEST_F ( UnloadTest , BrowserCloseInfiniteUnloadAlert ) {
 if ( base : : CommandLine : : ForCurrentProcess ( ) -> HasSwitch ( switches : : kSingleProcess ) ) return ;
 LoadUrlAndQuitBrowser ( INFINITE_UNLOAD_ALERT_HTML , "infiniteunloadalert" ) ;
 }