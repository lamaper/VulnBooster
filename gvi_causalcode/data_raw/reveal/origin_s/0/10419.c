IN_PROC_BROWSER_TEST_F ( UnloadTest , CrossSiteInfiniteBeforeUnloadAsync ) {
 if ( base : : CommandLine : : ForCurrentProcess ( ) -> HasSwitch ( switches : : kSingleProcess ) ) return ;
 NavigateToDataURL ( INFINITE_BEFORE_UNLOAD_HTML , "infinitebeforeunload" ) ;
 NavigateToNolistenersFileTwiceAsync ( ) ;
 }