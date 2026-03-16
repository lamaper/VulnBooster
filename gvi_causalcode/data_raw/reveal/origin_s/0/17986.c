IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , AbortReload ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url ( embedded_test_server ( ) -> GetURL ( "/title1.html" ) ) ;
 NavigateParams params ( browser ( ) , url , ui : : PAGE_TRANSITION_LINK ) ;
 content : : TestNavigationManager manager ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , url ) ;
 Navigate ( & params ) ;
 EXPECT_TRUE ( manager . WaitForRequestStart ( ) ) ;
 NavigateParams params2 ( browser ( ) , url , ui : : PAGE_TRANSITION_RELOAD ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 Navigate ( & params2 ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramAbortReloadBeforeCommit , 1 ) ;
 }