IN_PROC_BROWSER_TEST_F ( ClientHintsBrowserTest , ClientHintsHttpsSubresourceDifferentOrigin ) {
 base : : HistogramTester histogram_tester ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_with_lifetime_url ( ) ) ;
 histogram_tester . ExpectUniqueSample ( "ClientHints.UpdateEventCount" , 1 , 1 ) ;
 ContentSettingsForOneType client_hints_settings ;
 HostContentSettingsMap * host_content_settings_map = HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) ;
 host_content_settings_map -> GetSettingsForOneType ( CONTENT_SETTINGS_TYPE_CLIENT_HINTS , std : : string ( ) , & client_hints_settings ) ;
 ASSERT_EQ ( 1U , client_hints_settings . size ( ) ) ;
 host_content_settings_map -> SetWebsiteSettingDefaultScope ( GURL ( "https://foo.com/" ) , GURL ( ) , CONTENT_SETTINGS_TYPE_CLIENT_HINTS , std : : string ( ) , std : : make_unique < base : : Value > ( client_hints_settings . at ( 0 ) . setting_value -> Clone ( ) ) ) ;
 host_content_settings_map = HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) ;
 host_content_settings_map -> GetSettingsForOneType ( CONTENT_SETTINGS_TYPE_CLIENT_HINTS , std : : string ( ) , & client_hints_settings ) ;
 ASSERT_EQ ( 2U , client_hints_settings . size ( ) ) ;
 SetClientHintExpectationsOnMainFrame ( true ) ;
 SetClientHintExpectationsOnSubresources ( true ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , without_accept_ch_without_lifetime_img_localhost ( ) ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 content : : FetchHistogramsFromChildProcesses ( ) ;
 SubprocessMetricsProvider : : MergeHistogramDeltasForTesting ( ) ;



 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 content : : FetchHistogramsFromChildProcesses ( ) ;
 SubprocessMetricsProvider : : MergeHistogramDeltasForTesting ( ) ;



 EXPECT_EQ ( 0u , third_party_client_hints_count_seen ( ) ) ;
 }