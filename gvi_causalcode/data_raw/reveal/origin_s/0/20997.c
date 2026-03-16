IN_PROC_BROWSER_TEST_F ( ExtensionPreferenceApiTest , SessionOnlyIncognito ) {
 PrefService * prefs = profile_ -> GetPrefs ( ) ;
 prefs -> SetBoolean ( prefs : : kBlockThirdPartyCookies , false ) ;
 EXPECT_TRUE ( RunExtensionTestIncognito ( "preference/session_only_incognito" ) ) << message_ ;
 EXPECT_TRUE ( profile_ -> HasOffTheRecordProfile ( ) ) ;
 PrefService * otr_prefs = profile_ -> GetOffTheRecordProfile ( ) -> GetPrefs ( ) ;
 const PrefService : : Preference * pref = otr_prefs -> FindPreference ( prefs : : kBlockThirdPartyCookies ) ;
 ASSERT_TRUE ( pref ) ;
 EXPECT_TRUE ( pref -> IsExtensionControlled ( ) ) ;
 EXPECT_FALSE ( otr_prefs -> GetBoolean ( prefs : : kBlockThirdPartyCookies ) ) ;
 pref = prefs -> FindPreference ( prefs : : kBlockThirdPartyCookies ) ;
 ASSERT_TRUE ( pref ) ;
 EXPECT_FALSE ( pref -> IsExtensionControlled ( ) ) ;
 EXPECT_FALSE ( prefs -> GetBoolean ( prefs : : kBlockThirdPartyCookies ) ) ;
 }