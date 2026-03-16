IN_PROC_BROWSER_TEST_F ( ClientHintsBrowserTest , ClientHintsLifetimeNotAttachedJavaScriptBlocked ) {
 base : : HistogramTester histogram_tester ;
 ContentSettingsForOneType host_settings ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> GetSettingsForOneType ( CONTENT_SETTINGS_TYPE_CLIENT_HINTS , std : : string ( ) , & host_settings ) ;
 EXPECT_EQ ( 0u , host_settings . size ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_with_lifetime_url ( ) ) ;
 histogram_tester . ExpectUniqueSample ( "ClientHints.UpdateEventCount" , 1 , 1 ) ;
 content : : FetchHistogramsFromChildProcesses ( ) ;
 SubprocessMetricsProvider : : MergeHistogramDeltasForTesting ( ) ;
 histogram_tester . ExpectUniqueSample ( "ClientHints.UpdateSize" , 3 , 1 ) ;
 histogram_tester . ExpectUniqueSample ( "ClientHints.PersistDuration" , * 1000 , 1 ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> GetSettingsForOneType ( CONTENT_SETTINGS_TYPE_CLIENT_HINTS , std : : string ( ) , & host_settings ) ;
 EXPECT_EQ ( 1u , host_settings . size ( ) ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> SetContentSettingDefaultScope ( without_accept_ch_without_lifetime_url ( ) , GURL ( ) , CONTENT_SETTINGS_TYPE_JAVASCRIPT , std : : string ( ) , CONTENT_SETTING_BLOCK ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , without_accept_ch_without_lifetime_url ( ) ) ;
 EXPECT_EQ ( 0u , count_client_hints_headers_seen ( ) ) ;
 VerifyContentSettingsNotNotified ( ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> SetContentSettingDefaultScope ( without_accept_ch_without_lifetime_url ( ) , GURL ( ) , CONTENT_SETTINGS_TYPE_JAVASCRIPT , std : : string ( ) , CONTENT_SETTING_ALLOW ) ;
 SetClientHintExpectationsOnMainFrame ( true ) ;
 SetClientHintExpectationsOnSubresources ( true ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , without_accept_ch_without_lifetime_url ( ) ) ;



 }