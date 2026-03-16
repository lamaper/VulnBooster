IN_PROC_BROWSER_TEST_F ( SiteDetailsBrowserTest , VerifySiteInstanceCountInBrowsingInstanceWithExtensions ) {
 GURL tab_url = embedded_test_server ( ) -> GetURL ( "a.com" , "/cross_site_iframe_factory.html?a(b,c,d(e))" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , tab_url ) ;
 WebContents * tab = browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 0 ) ;
 scoped_refptr < TestMemoryDetails > details = new TestMemoryDetails ( ) ;
 details -> StartFetchAndWait ( ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.SiteInstancesPerBrowsingInstance" ) , HasOneSample ( DependingOnPolicy ( 1 , 1 , 5 ) ) ) ;
 const Extension * extension1 = CreateExtension ( "Extension One" , false ) ;
 content : : NavigateIframeToURL ( tab , "child-0" , extension1 -> GetResourceURL ( "/blank_iframe.html" ) ) ;
 details = new TestMemoryDetails ( ) ;
 details -> StartFetchAndWait ( ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.SiteInstancesPerBrowsingInstance" ) , HasOneSample ( DependingOnPolicy ( 1 , 2 , 5 ) ) ) ;
 const Extension * extension2 = CreateExtension ( "Extension Two" , true ) ;
 details = new TestMemoryDetails ( ) ;
 details -> StartFetchAndWait ( ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.SiteInstancesPerBrowsingInstance" ) , DependingOnPolicy ( ElementsAre ( Bucket ( 1 , 2 ) ) , ElementsAre ( Bucket ( 1 , 1 ) , Bucket ( 2 , 1 ) ) , ElementsAre ( Bucket ( 1 , 1 ) , Bucket ( 5 , 1 ) ) ) ) ;
 content : : NavigateIframeToURL ( tab , "child-1" , extension2 -> GetResourceURL ( "/blank_iframe.html" ) ) ;
 details = new TestMemoryDetails ( ) ;
 details -> StartFetchAndWait ( ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.SiteInstancesPerBrowsingInstance" ) , DependingOnPolicy ( ElementsAre ( Bucket ( 1 , 2 ) ) , ElementsAre ( Bucket ( 1 , 1 ) , Bucket ( 3 , 1 ) ) , ElementsAre ( Bucket ( 1 , 1 ) , Bucket ( 5 , 1 ) ) ) ) ;
 }