IN_PROC_BROWSER_TEST_F ( ExtensionPreferenceApiTest , OnChangeSplitWithNoOTRProfile ) {
 PrefService * prefs = profile_ -> GetPrefs ( ) ;
 prefs -> SetBoolean ( prefs : : kBlockThirdPartyCookies , true ) ;
 extensions : : ResultCatcher catcher ;
 ExtensionTestMessageListener loaded_incognito_test_listener ( "incognito loaded" , false ) ;
 ExtensionTestMessageListener change_pref_listener ( "change pref value" , false ) ;
 ASSERT_TRUE ( LoadExtensionIncognito ( test_data_dir_ . AppendASCII ( "preference" ) . AppendASCII ( "onchange_split_regular_only" ) ) ) ;
 ASSERT_TRUE ( change_pref_listener . WaitUntilSatisfied ( ) ) ;
 prefs -> SetBoolean ( prefs : : kBlockThirdPartyCookies , false ) ;
 EXPECT_TRUE ( catcher . GetNextResult ( ) ) << catcher . message ( ) ;
 EXPECT_FALSE ( loaded_incognito_test_listener . was_satisfied ( ) ) ;
 EXPECT_FALSE ( profile_ -> HasOffTheRecordProfile ( ) ) ;
 }