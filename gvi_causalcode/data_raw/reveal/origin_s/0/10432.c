IN_PROC_BROWSER_TEST_F ( ExtensionPreferenceApiTest , Clear ) {
 PrefService * prefs = profile_ -> GetPrefs ( ) ;
 prefs -> SetBoolean ( prefs : : kBlockThirdPartyCookies , true ) ;
 EXPECT_TRUE ( RunExtensionTest ( "preference/clear" ) ) << message_ ;
 const PrefService : : Preference * pref = prefs -> FindPreference ( prefs : : kBlockThirdPartyCookies ) ;
 ASSERT_TRUE ( pref ) ;
 EXPECT_FALSE ( pref -> IsExtensionControlled ( ) ) ;
 EXPECT_EQ ( true , prefs -> GetBoolean ( prefs : : kBlockThirdPartyCookies ) ) ;
 }