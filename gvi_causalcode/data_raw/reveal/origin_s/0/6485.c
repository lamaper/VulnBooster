IN_PROC_BROWSER_TEST_F ( ExtensionPreferenceApiTest , MAYBE_Standard ) {
 PrefService * prefs = profile_ -> GetPrefs ( ) ;
 prefs -> SetBoolean ( prefs : : kAlternateErrorPagesEnabled , false ) ;
 prefs -> SetBoolean ( autofill : : prefs : : kAutofillEnabledDeprecated , false ) ;
 prefs -> SetBoolean ( autofill : : prefs : : kAutofillCreditCardEnabled , false ) ;
 prefs -> SetBoolean ( autofill : : prefs : : kAutofillProfileEnabled , false ) ;
 prefs -> SetBoolean ( prefs : : kBlockThirdPartyCookies , true ) ;
 prefs -> SetBoolean ( prefs : : kEnableHyperlinkAuditing , false ) ;
 prefs -> SetBoolean ( prefs : : kEnableReferrers , false ) ;
 prefs -> SetBoolean ( prefs : : kOfferTranslateEnabled , false ) ;
 prefs -> SetInteger ( prefs : : kNetworkPredictionOptions , chrome_browser_net : : NETWORK_PREDICTION_NEVER ) ;
 prefs -> SetBoolean ( password_manager : : prefs : : kCredentialsEnableService , false ) ;
 prefs -> SetBoolean ( prefs : : kSafeBrowsingEnabled , false ) ;
 prefs -> SetBoolean ( prefs : : kSearchSuggestEnabled , false ) ;
 prefs -> SetBoolean ( prefs : : kWebRTCMultipleRoutesEnabled , false ) ;
 prefs -> SetBoolean ( prefs : : kWebRTCNonProxiedUdpEnabled , false ) ;
 prefs -> SetString ( prefs : : kWebRTCIPHandlingPolicy , content : : kWebRTCIPHandlingDefaultPublicInterfaceOnly ) ;
 const char kExtensionPath [ ] = "preference/standard" ;
 EXPECT_TRUE ( RunExtensionSubtest ( kExtensionPath , "test.html" ) ) << message_ ;
 CheckPreferencesSet ( ) ;
 ReloadExtension ( last_loaded_extension_id ( ) ) ;
 CheckPreferencesSet ( ) ;
 extensions : : TestExtensionRegistryObserver observer ( extensions : : ExtensionRegistry : : Get ( profile_ ) , last_loaded_extension_id ( ) ) ;
 UninstallExtension ( last_loaded_extension_id ( ) ) ;
 observer . WaitForExtensionUninstalled ( ) ;
 CheckPreferencesCleared ( ) ;
 LoadExtension ( test_data_dir_ . AppendASCII ( kExtensionPath ) ) ;
 CheckPreferencesCleared ( ) ;
 }