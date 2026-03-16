IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , DISABLED_BadXhtml ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/page_load_metrics/badxml.xhtml" ) ) ;
 NavigateToUntrackedUrl ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstLayout , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstPaint , 0 ) ;
 histogram_tester_ . ExpectBucketCount ( page_load_metrics : : internal : : kErrorEvents , page_load_metrics : : ERR_BAD_TIMING_IPC_INVALID_TIMING , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( page_load_metrics : : internal : : kPageLoadTimingStatus , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( page_load_metrics : : internal : : kPageLoadTimingStatus , page_load_metrics : : internal : : INVALID_ORDER_FIRST_LAYOUT_FIRST_PAINT , 1 ) ;
 }