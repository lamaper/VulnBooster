IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , NewPageInNewForegroundTab ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 NavigateParams params ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/title1.html" ) , ui : : PAGE_TRANSITION_LINK ) ;
 params . disposition = WindowOpenDisposition : : NEW_FOREGROUND_TAB ;
 Navigate ( & params ) ;
 auto waiter = std : : make_unique < PageLoadMetricsWaiter > ( params . target_contents ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramLoad , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kBackgroundHistogramLoad , 0 ) ;
 }