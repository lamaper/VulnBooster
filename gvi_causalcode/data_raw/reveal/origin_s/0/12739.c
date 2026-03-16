IN_PROC_BROWSER_TEST_F ( UnloadTest , CrossSiteInfiniteUnloadAsync ) {
 if ( base : : CommandLine : : ForCurrentProcess ( ) -> HasSwitch ( switches : : kSingleProcess ) ) return ;
 NavigateToDataURL ( INFINITE_UNLOAD_HTML , "infiniteunload" ) ;
 NavigateToNolistenersFileTwiceAsync ( ) ;
 }