IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , FirstMeaningfulPaintRecorded ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_MEANINGFUL_PAINT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/title1.html" ) ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectUniqueSample ( internal : : kHistogramFirstMeaningfulPaintStatus , internal : : FIRST_MEANINGFUL_PAINT_RECORDED , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstMeaningfulPaint , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramParseStartToFirstMeaningfulPaint , 1 ) ;
 }