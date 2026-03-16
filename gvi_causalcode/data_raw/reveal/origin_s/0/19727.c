IN_PROC_BROWSER_TEST_F ( ClientHintsBrowserTest , ClientHintsNoLifetimeCookiesNotAllowed ) {
 base : : HistogramTester histogram_tester ;
 ContentSettingsForOneType host_settings ;
 scoped_refptr < content_settings : : CookieSettings > cookie_settings_ = CookieSettingsFactory : : GetForProfile ( browser ( ) -> profile ( ) ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> GetSettingsForOneType ( CONTENT_SETTINGS_TYPE_CLIENT_HINTS , std : : string ( ) , & host_settings ) ;
 EXPECT_EQ ( 0u , host_settings . size ( ) ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> SetContentSettingDefaultScope ( accept_ch_without_lifetime_img_localhost ( ) , GURL ( ) , CONTENT_SETTINGS_TYPE_COOKIES , std : : string ( ) , CONTENT_SETTING_BLOCK ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_without_lifetime_img_localhost ( ) ) ;
 EXPECT_EQ ( 0u , count_client_hints_headers_seen ( ) ) ;
 EXPECT_EQ ( 0u , third_party_client_hints_count_seen ( ) ) ;
 VerifyContentSettingsNotNotified ( ) ;
 cookie_settings_ -> SetCookieSetting ( accept_ch_without_lifetime_img_localhost ( ) , CONTENT_SETTING_ALLOW ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 SetClientHintExpectationsOnSubresources ( true ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_without_lifetime_img_localhost ( ) ) ;
 EXPECT_EQ ( 3u , count_client_hints_headers_seen ( ) ) ;
 EXPECT_EQ ( 2u , third_party_request_count_seen ( ) ) ;
 EXPECT_EQ ( 0u , third_party_client_hints_count_seen ( ) ) ;
 SetClientHintExpectationsOnSubresources ( false ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> SetContentSettingDefaultScope ( accept_ch_without_lifetime_img_localhost ( ) , GURL ( ) , CONTENT_SETTINGS_TYPE_COOKIES , std : : string ( ) , CONTENT_SETTING_BLOCK ) ;
 base : : RunLoop ( ) . RunUntilIdle ( ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_without_lifetime_img_localhost ( ) ) ;
 EXPECT_EQ ( 3u , count_client_hints_headers_seen ( ) ) ;
 EXPECT_EQ ( 3u , third_party_request_count_seen ( ) ) ;
 EXPECT_EQ ( 0u , third_party_client_hints_count_seen ( ) ) ;
 }