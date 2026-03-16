IN_PROC_BROWSER_TEST_F ( PrefsFunctionalTest , PRE_TestHomepagePrefs ) {
 GURL home_page_url ( "http://www.google.com" ) ;
 PrefService * prefs = browser ( ) -> profile ( ) -> GetPrefs ( ) ;
 prefs -> SetBoolean ( prefs : : kHomePageIsNewTabPage , false ) ;
 const PrefService : : Preference * pref = prefs -> FindPreference ( prefs : : kHomePage ) ;
 if ( pref && ! pref -> IsManaged ( ) ) {
 prefs -> SetString ( prefs : : kHomePage , home_page_url . spec ( ) ) ;
 }
 }