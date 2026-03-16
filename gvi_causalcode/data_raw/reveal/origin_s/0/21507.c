IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , NoStatePrefetchObserverNoStore ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_CONTENTFUL_PAINT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "ostore.html" ) ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( "Prerender.none_PrefetchTTFCP.Reference.NoStore.Visible" , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( "Prerender.none_PrefetchTTFCP.Reference.Cacheable.Visible" , 0 ) ;
 }