IN_PROC_BROWSER_TEST_F ( SiteDetailsBrowserTest , ExtensionWithTwoWebIframes ) {
 scoped_refptr < TestMemoryDetails > details = new TestMemoryDetails ( ) ;
 details -> StartFetchAndWait ( ) ;
 const Extension * extension = CreateExtension ( "Test Extension" , false ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , extension -> GetResourceURL ( "/two_http_iframes.html" ) ) ;
 details = new TestMemoryDetails ( ) ;
 details -> StartFetchAndWait ( ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.CurrentRendererProcessCount" ) , HasOneSample ( GetRenderProcessCount ( ) ) ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.IsolateNothingProcessCountEstimate" ) , HasOneSample ( 1 ) ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.IsolateExtensionsProcessCountEstimate" ) , HasOneSample ( 2 ) ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.IsolateExtensionsProcessCountLowerBound" ) , HasOneSample ( 2 ) ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.IsolateExtensionsProcessCountNoLimit" ) , HasOneSample ( 2 ) ) ;
 EXPECT_THAT ( GetRenderProcessCount ( ) , DependingOnPolicy ( 1 , 3 , 3 ) ) ;
 EXPECT_THAT ( details -> GetOutOfProcessIframeCount ( ) , DependingOnPolicy ( 0 , 2 , 2 ) ) ;
 }