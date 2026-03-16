IN_PROC_BROWSER_TEST_F ( ClientHintsBrowserTest , ClientHintsLifetimeNotPersistedCookiesBlocked ) {
 scoped_refptr < content_settings : : CookieSettings > cookie_settings_ = CookieSettingsFactory : : GetForProfile ( browser ( ) -> profile ( ) ) ;
 base : : HistogramTester histogram_tester ;
 ContentSettingsForOneType host_settings ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> SetContentSettingDefaultScope ( accept_ch_without_lifetime_url ( ) , GURL ( ) , CONTENT_SETTINGS_TYPE_COOKIES , std : : string ( ) , CONTENT_SETTING_BLOCK ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_with_lifetime_url ( ) ) ;
 histogram_tester . ExpectTotalCount ( "ClientHints.UpdateEventCount" , 0 ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> GetSettingsForOneType ( CONTENT_SETTINGS_TYPE_CLIENT_HINTS , std : : string ( ) , & host_settings ) ;
 EXPECT_EQ ( 0u , host_settings . size ( ) ) ;
 VerifyContentSettingsNotNotified ( ) ;
 cookie_settings_ -> SetCookieSetting ( accept_ch_without_lifetime_url ( ) , CONTENT_SETTING_ALLOW ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_with_lifetime_url ( ) ) ;
 histogram_tester . ExpectTotalCount ( "ClientHints.UpdateEventCount" , 1 ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> GetSettingsForOneType ( CONTENT_SETTINGS_TYPE_CLIENT_HINTS , std : : string ( ) , & host_settings ) ;
 EXPECT_EQ ( 1u , host_settings . size ( ) ) ;
 }