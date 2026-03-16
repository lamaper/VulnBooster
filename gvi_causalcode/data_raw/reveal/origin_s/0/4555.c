IN_PROC_BROWSER_TEST_F ( ExtensionPreferenceApiTest , PersistentIncognito ) {
 PrefService * prefs = profile_ -> GetPrefs ( ) ;
 prefs -> SetBoolean ( prefs : : kBlockThirdPartyCookies , false ) ;
 EXPECT_TRUE ( RunExtensionTestIncognito ( "preference/persistent_incognito" ) ) << message_ ;
 EXPECT_FALSE ( profile_ -> HasOffTheRecordProfile ( ) ) ;
 PrefService * otr_prefs = profile_ -> GetOffTheRecordProfile ( ) -> GetPrefs ( ) ;
 const PrefService : : Preference * pref = otr_prefs -> FindPreference ( prefs : : kBlockThirdPartyCookies ) ;
 ASSERT_TRUE ( pref ) ;
 EXPECT_TRUE ( pref -> IsExtensionControlled ( ) ) ;
 EXPECT_TRUE ( otr_prefs -> GetBoolean ( prefs : : kBlockThirdPartyCookies ) ) ;
 pref = prefs -> FindPreference ( prefs : : kBlockThirdPartyCookies ) ;
 ASSERT_TRUE ( pref ) ;
 EXPECT_FALSE ( pref -> IsExtensionControlled ( ) ) ;
 EXPECT_FALSE ( prefs -> GetBoolean ( prefs : : kBlockThirdPartyCookies ) ) ;
 }