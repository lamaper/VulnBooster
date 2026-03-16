IN_PROC_BROWSER_TEST_F ( ProfileBrowserTest , URLFetcherUsingMainContextDuringShutdown ) {
 StartActiveFetcherDuringProfileShutdownTest ( browser ( ) -> profile ( ) -> GetRequestContext ( ) ) ;
 }