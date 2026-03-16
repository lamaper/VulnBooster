IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , NoDocumentWrite ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_CONTENTFUL_PAINT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/title1.html" ) ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstContentfulPaint , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramDocWriteBlockParseStartToFirstContentfulPaint , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramDocWriteBlockCount , 0 ) ;
 }