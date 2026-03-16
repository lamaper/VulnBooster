IN_PROC_BROWSER_TEST_F ( ClientHintsBrowserTest , ClientHintsNoLifetimeScriptNotAllowed ) {
 base : : HistogramTester histogram_tester ;
 ContentSettingsForOneType host_settings ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> GetSettingsForOneType ( CONTENT_SETTINGS_TYPE_CLIENT_HINTS , std : : string ( ) , & host_settings ) ;
 EXPECT_EQ ( 0u , host_settings . size ( ) ) ;
 SetClientHintExpectationsOnSubresources ( false ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> SetContentSettingDefaultScope ( accept_ch_without_lifetime_img_localhost ( ) , GURL ( ) , CONTENT_SETTINGS_TYPE_JAVASCRIPT , std : : string ( ) , CONTENT_SETTING_BLOCK ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_without_lifetime_img_localhost ( ) ) ;
 EXPECT_EQ ( 0u , count_client_hints_headers_seen ( ) ) ;
 EXPECT_EQ ( 1u , third_party_request_count_seen ( ) ) ;
 EXPECT_EQ ( 0u , third_party_client_hints_count_seen ( ) ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> SetContentSettingDefaultScope ( accept_ch_without_lifetime_img_localhost ( ) , GURL ( ) , CONTENT_SETTINGS_TYPE_JAVASCRIPT , std : : string ( ) , CONTENT_SETTING_ALLOW ) ;
 SetClientHintExpectationsOnSubresources ( true ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_without_lifetime_img_localhost ( ) ) ;
 EXPECT_EQ ( 3u , count_client_hints_headers_seen ( ) ) ;
 EXPECT_EQ ( 2u , third_party_request_count_seen ( ) ) ;
 EXPECT_EQ ( 0u , third_party_client_hints_count_seen ( ) ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> ClearSettingsForOneType ( CONTENT_SETTINGS_TYPE_JAVASCRIPT ) ;
 SetClientHintExpectationsOnSubresources ( false ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> SetContentSettingDefaultScope ( accept_ch_without_lifetime_img_localhost ( ) , GURL ( ) , CONTENT_SETTINGS_TYPE_JAVASCRIPT , std : : string ( ) , CONTENT_SETTING_BLOCK ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_without_lifetime_img_localhost ( ) ) ;
 EXPECT_EQ ( 3u , count_client_hints_headers_seen ( ) ) ;
 EXPECT_EQ ( 3u , third_party_request_count_seen ( ) ) ;
 EXPECT_EQ ( 0u , third_party_client_hints_count_seen ( ) ) ;
 }