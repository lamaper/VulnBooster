IN_PROC_BROWSER_TEST_F ( ClientHintsBrowserTest , ClientHintsHttpsIncognito ) {
 for ( size_t i = 0 ;
 i < 2 ;
 ++ i ) {
 base : : HistogramTester histogram_tester ;
 Browser * incognito = CreateIncognitoBrowser ( ) ;
 ui_test_utils : : NavigateToURL ( incognito , accept_ch_with_lifetime_url ( ) ) ;
 histogram_tester . ExpectUniqueSample ( "ClientHints.UpdateEventCount" , 1 , 1 ) ;
 content : : FetchHistogramsFromChildProcesses ( ) ;
 SubprocessMetricsProvider : : MergeHistogramDeltasForTesting ( ) ;
 histogram_tester . ExpectUniqueSample ( "ClientHints.UpdateSize" , 3 , 1 ) ;
 EXPECT_LE ( 1u , histogram_tester . GetAllSamples ( "ClientHints.CountRulesReceived" ) . size ( ) ) ;
 for ( const auto & bucket : histogram_tester . GetAllSamples ( "ClientHints.CountRulesReceived" ) ) {
 EXPECT_EQ ( 0 , bucket . min ) ;
 }
 histogram_tester . ExpectUniqueSample ( "ClientHints.PersistDuration" , * 1000 , 1 ) ;
 CloseBrowserSynchronously ( incognito ) ;
 }
 }