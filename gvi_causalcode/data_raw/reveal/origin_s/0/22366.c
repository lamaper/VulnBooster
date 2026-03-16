IN_PROC_BROWSER_TEST_F ( PrefsFunctionalTest , PRE_TestPrivacySecurityPrefs ) {
 PrefService * prefs = browser ( ) -> profile ( ) -> GetPrefs ( ) ;
 static_assert ( chrome_browser_net : : NETWORK_PREDICTION_DEFAULT != chrome_browser_net : : NETWORK_PREDICTION_NEVER , "PrefsFunctionalTest.TestPrivacySecurityPrefs relies on " "predictive network actions being enabled by default." ) ;
 EXPECT_EQ ( chrome_browser_net : : NETWORK_PREDICTION_DEFAULT , prefs -> GetInteger ( prefs : : kNetworkPredictionOptions ) ) ;
 prefs -> SetInteger ( prefs : : kNetworkPredictionOptions , chrome_browser_net : : NETWORK_PREDICTION_NEVER ) ;
 EXPECT_TRUE ( prefs -> GetBoolean ( prefs : : kSafeBrowsingEnabled ) ) ;
 prefs -> SetBoolean ( prefs : : kSafeBrowsingEnabled , false ) ;
 EXPECT_TRUE ( prefs -> GetBoolean ( prefs : : kAlternateErrorPagesEnabled ) ) ;
 prefs -> SetBoolean ( prefs : : kAlternateErrorPagesEnabled , false ) ;
 EXPECT_TRUE ( prefs -> GetBoolean ( prefs : : kSearchSuggestEnabled ) ) ;
 prefs -> SetBoolean ( prefs : : kSearchSuggestEnabled , false ) ;
 }