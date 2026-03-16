IN_PROC_BROWSER_TEST_F ( SiteDetailsBrowserTest , PlatformAppsNotIsolated ) {
 if ( content : : AreAllSitesIsolatedForTesting ( ) ) return ;
 CreateAppWithSandboxPage ( "Extension One" ) ;
 scoped_refptr < TestMemoryDetails > details = new TestMemoryDetails ( ) ;
 details -> StartFetchAndWait ( ) ;
 EXPECT_EQ ( 0 , details -> GetOutOfProcessIframeCount ( ) ) ;
 }