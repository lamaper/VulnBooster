IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , NoAbortMetricsOnClientRedirect ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL first_url ( embedded_test_server ( ) -> GetURL ( "/title1.html" ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , first_url ) ;
 GURL second_url ( embedded_test_server ( ) -> GetURL ( "/title2.html" ) ) ;
 NavigateParams params ( browser ( ) , second_url , ui : : PAGE_TRANSITION_LINK ) ;
 content : : TestNavigationManager manager ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , second_url ) ;
 Navigate ( & params ) ;
 EXPECT_TRUE ( manager . WaitForRequestStart ( ) ) ;
 {
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 EXPECT_TRUE ( content : : ExecuteScript ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , "window.location.reload();
" ) ) ;
 waiter -> Wait ( ) ;
 }
 manager . WaitForNavigationFinished ( ) ;
 EXPECT_TRUE ( histogram_tester_ . GetTotalCountsForPrefix ( "PageLoad.Experimental.AbortTiming." ) . empty ( ) ) ;
 }