IN_PROC_BROWSER_TEST_F ( PrefsFunctionalTest , PRE_TestHomepageNewTabpagePrefs ) {
 browser ( ) -> profile ( ) -> GetPrefs ( ) -> SetBoolean ( prefs : : kHomePageIsNewTabPage , true ) ;
 }