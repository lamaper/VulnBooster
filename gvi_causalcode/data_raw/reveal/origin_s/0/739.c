IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , AbortNewNavigation ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url ( embedded_test_server ( ) -> GetURL ( "/title1.html" ) ) ;
 NavigateParams params ( browser ( ) , url , ui : : PAGE_TRANSITION_LINK ) ;
 content : : TestNavigationManager manager ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , url ) ;
 Navigate ( & params ) ;
 EXPECT_TRUE ( manager . WaitForRequestStart ( ) ) ;
 GURL url2 ( embedded_test_server ( ) -> GetURL ( "/title2.html" ) ) ;
 NavigateParams params2 ( browser ( ) , url2 , ui : : PAGE_TRANSITION_FROM_ADDRESS_BAR ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 Navigate ( & params2 ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramAbortNewNavigationBeforeCommit , 1 ) ;
 }