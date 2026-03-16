IN_PROC_BROWSER_TEST_F ( ClientHintsBrowserTest , ClientHintsLifetimeNotPersistedJavaScriptBlocked ) {
 ContentSettingsForOneType host_settings ;
 ui_test_utils : : NavigateToURL ( browser ( ) , without_accept_ch_without_lifetime_url ( ) ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> SetContentSettingDefaultScope ( accept_ch_with_lifetime_url ( ) , GURL ( ) , CONTENT_SETTINGS_TYPE_JAVASCRIPT , std : : string ( ) , CONTENT_SETTING_BLOCK ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_with_lifetime_url ( ) ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> GetSettingsForOneType ( CONTENT_SETTINGS_TYPE_CLIENT_HINTS , std : : string ( ) , & host_settings ) ;
 EXPECT_EQ ( 0u , host_settings . size ( ) ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> SetContentSettingDefaultScope ( accept_ch_with_lifetime_url ( ) , GURL ( ) , CONTENT_SETTINGS_TYPE_JAVASCRIPT , std : : string ( ) , CONTENT_SETTING_ALLOW ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , accept_ch_with_lifetime_url ( ) ) ;
 HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) -> GetSettingsForOneType ( CONTENT_SETTINGS_TYPE_CLIENT_HINTS , std : : string ( ) , & host_settings ) ;
 EXPECT_EQ ( 1u , host_settings . size ( ) ) ;
 }