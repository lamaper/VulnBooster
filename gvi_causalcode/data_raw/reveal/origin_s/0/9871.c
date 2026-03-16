IN_PROC_BROWSER_TEST_F ( ExtensionPreferenceApiTest , OnChange ) {
 EXPECT_TRUE ( RunExtensionTestIncognito ( "preference/onchange" ) ) << message_ ;
 }