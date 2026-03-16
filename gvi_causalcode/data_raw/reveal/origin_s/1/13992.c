IN_PROC_BROWSER_TEST_F ( ProfileBrowserTest , URLFetcherUsingMediaContextDuringShutdown ) {
 StartActiveFetcherDuringProfileShutdownTest ( content : : BrowserContext : : GetDefaultStoragePartition ( browser ( ) -> profile ( ) ) -> GetMediaURLRequestContext ( ) ) ;
 }