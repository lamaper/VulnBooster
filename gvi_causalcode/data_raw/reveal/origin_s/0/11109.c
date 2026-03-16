IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , AbortMultiple ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url ( embedded_test_server ( ) -> GetURL ( "/title1.html" ) ) ;
 NavigateParams params ( browser ( ) , url , ui : : PAGE_TRANSITION_LINK ) ;
 content : : TestNavigationManager manager ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , url ) ;
 Navigate ( & params ) ;
 EXPECT_TRUE ( manager . WaitForRequestStart ( ) ) ;
 GURL url2 ( embedded_test_server ( ) -> GetURL ( "/title2.html" ) ) ;
 NavigateParams params2 ( browser ( ) , url2 , ui : : PAGE_TRANSITION_TYPED ) ;
 content : : TestNavigationManager manager2 ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , url2 ) ;
 Navigate ( & params2 ) ;
 EXPECT_TRUE ( manager2 . WaitForRequestStart ( ) ) ;
 manager . WaitForNavigationFinished ( ) ;
 GURL url3 ( embedded_test_server ( ) -> GetURL ( "/title3.html" ) ) ;
 NavigateParams params3 ( browser ( ) , url3 , ui : : PAGE_TRANSITION_TYPED ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 Navigate ( & params3 ) ;
 waiter -> Wait ( ) ;
 manager2 . WaitForNavigationFinished ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramAbortNewNavigationBeforeCommit , 2 ) ;
 }