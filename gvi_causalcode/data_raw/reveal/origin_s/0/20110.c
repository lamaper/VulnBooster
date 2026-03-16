IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , DocumentWriteReload ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_CONTENTFUL_PAINT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/page_load_metrics/document_write_script_block.html" ) ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramDocWriteBlockParseStartToFirstContentfulPaint , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramDocWriteBlockCount , 1 ) ;
 waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : DOCUMENT_WRITE_BLOCK_RELOAD ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_CONTENTFUL_PAINT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/page_load_metrics/document_write_script_block.html" ) ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramDocWriteBlockReloadCount , 1 ) ;
 waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : DOCUMENT_WRITE_BLOCK_RELOAD ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_CONTENTFUL_PAINT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/page_load_metrics/document_write_script_block.html" ) ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramDocWriteBlockParseStartToFirstContentfulPaint , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramDocWriteBlockReloadCount , 2 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramDocWriteBlockCount , 1 ) ;
 }