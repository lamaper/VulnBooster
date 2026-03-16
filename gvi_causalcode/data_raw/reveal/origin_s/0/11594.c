IN_PROC_BROWSER_TEST_F ( PrefsFunctionalTest , TestHomepagePrefs ) {
 GURL home_page_url ( "http://www.google.com" ) ;
 PrefService * prefs = browser ( ) -> profile ( ) -> GetPrefs ( ) ;
 EXPECT_FALSE ( prefs -> GetBoolean ( prefs : : kHomePageIsNewTabPage ) ) ;
 EXPECT_EQ ( home_page_url . spec ( ) , prefs -> GetString ( prefs : : kHomePage ) ) ;
 }