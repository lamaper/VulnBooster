IN_PROC_BROWSER_TEST_F ( PrefsFunctionalTest , TestPrivacySecurityPrefs ) {
 PrefService * prefs = browser ( ) -> profile ( ) -> GetPrefs ( ) ;
 EXPECT_EQ ( chrome_browser_net : : NETWORK_PREDICTION_NEVER , prefs -> GetInteger ( prefs : : kNetworkPredictionOptions ) ) ;
 EXPECT_FALSE ( prefs -> GetBoolean ( prefs : : kSafeBrowsingEnabled ) ) ;
 EXPECT_FALSE ( prefs -> GetBoolean ( prefs : : kAlternateErrorPagesEnabled ) ) ;
 EXPECT_FALSE ( prefs -> GetBoolean ( prefs : : kSearchSuggestEnabled ) ) ;
 }