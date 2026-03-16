IN_PROC_BROWSER_TEST_F ( ExtensionPreferenceApiTest , DISABLED_IncognitoDisabled ) {
 EXPECT_FALSE ( RunExtensionTest ( "preference/persistent_incognito" ) ) ;
 }