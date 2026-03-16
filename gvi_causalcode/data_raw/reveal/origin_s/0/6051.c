IN_PROC_BROWSER_TEST_F ( SiteDetailsBrowserTest , VerifySiteInstanceCountInBrowsingInstance ) {
 GURL abcdefghi_url = embedded_test_server ( ) -> GetURL ( "a.com" , "/cross_site_iframe_factory.html?a(b(a(b,c,d,e,f,g,h)),c,d,e,i(f))" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , abcdefghi_url ) ;
 scoped_refptr < TestMemoryDetails > details = new TestMemoryDetails ( ) ;
 details -> StartFetchAndWait ( ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.SiteInstancesPerBrowsingInstance" ) , HasOneSample ( DependingOnPolicy ( 1 , 1 , 9 ) ) ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.ProxyCount" ) , HasOneSample ( DependingOnPolicy ( 0 , 0 , 114 ) ) ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.ProxyCountPerBrowsingInstance" ) , HasOneSample ( DependingOnPolicy ( 0 , 0 , 114 ) ) ) ;
 GURL dcbae_url = embedded_test_server ( ) -> GetURL ( "a.com" , "/cross_site_iframe_factory.html?d(c(b(j(k))))" ) ;
 ui_test_utils : : UrlLoadObserver load_complete ( dcbae_url , content : : NotificationService : : AllSources ( ) ) ;
 ASSERT_EQ ( 1 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 ASSERT_TRUE ( content : : ExecuteScript ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , "window.open('" + dcbae_url . spec ( ) + "');
" ) ) ;
 ASSERT_EQ ( 2 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 load_complete . Wait ( ) ;
 details = new TestMemoryDetails ( ) ;
 details -> StartFetchAndWait ( ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.SiteInstancesPerBrowsingInstance" ) , HasOneSample ( DependingOnPolicy ( 1 , 1 , 11 ) ) ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.ProxyCount" ) , HasOneSample ( DependingOnPolicy ( 0 , 0 , 160 ) ) ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.ProxyCountPerBrowsingInstance" ) , HasOneSample ( DependingOnPolicy ( 0 , 0 , 160 ) ) ) ;
 GURL abcd_url = embedded_test_server ( ) -> GetURL ( "a.com" , "/cross_site_iframe_factory.html?a(b(c(d())))" ) ;
 AddTabAtIndex ( 1 , abcd_url , ui : : PAGE_TRANSITION_TYPED ) ;
 details = new TestMemoryDetails ( ) ;
 details -> StartFetchAndWait ( ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.SiteInstancesPerBrowsingInstance" ) , DependingOnPolicy ( ElementsAre ( Sample ( 1 , 2 ) ) , ElementsAre ( Sample ( 1 , 2 ) ) , ElementsAre ( Sample ( 4 , 1 ) , Sample ( 11 , 1 ) ) ) ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.ProxyCount" ) , HasOneSample ( DependingOnPolicy ( 0 , 0 , 160 ) ) ) ;
 EXPECT_THAT ( details -> uma ( ) -> GetAllSamples ( "SiteIsolation.ProxyCountPerBrowsingInstance" ) , DependingOnPolicy ( ElementsAre ( Sample ( 0 , 2 ) ) , ElementsAre ( Sample ( 0 , 2 ) ) , ElementsAre ( Sample ( 12 , 1 ) , Sample ( 160 , 1 ) ) ) ) ;
 }