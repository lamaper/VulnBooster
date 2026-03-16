IN_PROC_BROWSER_TEST_F ( ClientHintsBrowserTest , ClientHintsHttps ) {
 base : : HistogramTester histogram_tester ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_with_lifetime_url ( ) ) ;
 histogram_tester . ExpectUniqueSample ( "ClientHints.UpdateEventCount" , 1 , 1 ) ;
 content : : FetchHistogramsFromChildProcesses ( ) ;
 SubprocessMetricsProvider : : MergeHistogramDeltasForTesting ( ) ;
 histogram_tester . ExpectUniqueSample ( "ClientHints.UpdateSize" , 3 , 1 ) ;
 histogram_tester . ExpectUniqueSample ( "ClientHints.PersistDuration" , * 1000 , 1 ) ;
 }