IN_PROC_BROWSER_TEST_F ( ClientHintsBrowserTest , NoClientHintsHttps ) {
 base : : HistogramTester histogram_tester ;
 ui_test_utils : : NavigateToURL ( browser ( ) , without_accept_ch_without_lifetime_url ( ) ) ;
 histogram_tester . ExpectTotalCount ( "ClientHints.UpdateEventCount" , 0 ) ;
 content : : FetchHistogramsFromChildProcesses ( ) ;
 SubprocessMetricsProvider : : MergeHistogramDeltasForTesting ( ) ;
 histogram_tester . ExpectTotalCount ( "ClientHints.UpdateSize" , 0 ) ;
 histogram_tester . ExpectTotalCount ( "ClientHints.PersistDuration" , 0 ) ;
 }