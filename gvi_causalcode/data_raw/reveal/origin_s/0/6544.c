IN_PROC_BROWSER_TEST_F ( UnloadTest , DISABLED_CrossSiteInfiniteBeforeUnloadSync ) {
 if ( base : : CommandLine : : ForCurrentProcess ( ) -> HasSwitch ( switches : : kSingleProcess ) ) return ;
 NavigateToDataURL ( INFINITE_BEFORE_UNLOAD_HTML , "infinitebeforeunload" ) ;
 NavigateToNolistenersFileTwice ( ) ;
 }