IN_PROC_BROWSER_TEST_F ( ProfileBrowserTest , URLFetcherUsingExtensionContextDuringShutdown ) {
 StartActiveFetcherDuringProfileShutdownTest ( browser ( ) -> profile ( ) -> GetRequestContextForExtensions ( ) ) ;
 }