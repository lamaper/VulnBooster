IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , MAYBE_AbortClose ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url ( embedded_test_server ( ) -> GetURL ( "/title1.html" ) ) ;
 NavigateParams params ( browser ( ) , url , ui : : PAGE_TRANSITION_LINK ) ;
 content : : TestNavigationManager manager ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , url ) ;
 Navigate ( & params ) ;
 EXPECT_TRUE ( manager . WaitForRequestStart ( ) ) ;
 browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) -> Close ( ) ;
 manager . WaitForNavigationFinished ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramAbortCloseBeforeCommit , 1 ) ;
 }