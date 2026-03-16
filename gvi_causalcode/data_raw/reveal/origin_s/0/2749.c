IN_PROC_BROWSER_TEST_F ( ClientHintsBrowserTest , DisregardPersistenceRequestIframe ) {
 base : : HistogramTester histogram_tester ;
 ContentSettingsForOneType host_settings ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> GetSettingsForOneType ( CONTENT_SETTINGS_TYPE_CLIENT_HINTS , std : : string ( ) , & host_settings ) ;
 EXPECT_EQ ( 0u , host_settings . size ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_without_lifetime_with_iframe_url ( ) ) ;
 histogram_tester . ExpectTotalCount ( "ClientHints.UpdateEventCount" , 0 ) ;
 content : : FetchHistogramsFromChildProcesses ( ) ;
 SubprocessMetricsProvider : : MergeHistogramDeltasForTesting ( ) ;
 histogram_tester . ExpectTotalCount ( "ClientHints.UpdateSize" , 0 ) ;
 histogram_tester . ExpectTotalCount ( "ClientHints.PersistDuration" , 0 ) ;
 }