IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , NewPage ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url = embedded_test_server ( ) -> GetURL ( "/title1.html" ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_PAINT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramDomContentLoaded , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramLoad , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstLayout , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstPaint , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramParseDuration , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramParseBlockedOnScriptLoad , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramParseBlockedOnScriptExecution , 1 ) ;
 NavigateToUntrackedUrl ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramPageLoadTotalBytes , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramPageTimingForegroundDuration , 1 ) ;
 const auto & entries = test_ukm_recorder_ -> GetMergedEntriesByName ( internal : : kUkmPageLoadEventName ) ;
 EXPECT_EQ ( 1u , entries . size ( ) ) ;
 for ( const auto & kv : entries ) {
 test_ukm_recorder_ -> ExpectEntrySourceHasUrl ( kv . second . get ( ) , url ) ;
 EXPECT_TRUE ( test_ukm_recorder_ -> EntryHasMetric ( kv . second . get ( ) , internal : : kUkmDomContentLoadedName ) ) ;
 EXPECT_TRUE ( test_ukm_recorder_ -> EntryHasMetric ( kv . second . get ( ) , internal : : kUkmLoadEventName ) ) ;
 EXPECT_TRUE ( test_ukm_recorder_ -> EntryHasMetric ( kv . second . get ( ) , internal : : kUkmFirstPaintName ) ) ;
 EXPECT_TRUE ( test_ukm_recorder_ -> EntryHasMetric ( kv . second . get ( ) , internal : : kUkmFirstContentfulPaintName ) ) ;
 }
 EXPECT_FALSE ( NoPageLoadMetricsRecorded ( ) ) ;
 }