IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , NoStatePrefetchObserverCacheable ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_CONTENTFUL_PAINT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/title1.html" ) ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( "Prerender.none_PrefetchTTFCP.Reference.NoStore.Visible" , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( "Prerender.none_PrefetchTTFCP.Reference.Cacheable.Visible" , 1 ) ;
 }