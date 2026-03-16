IN_PROC_BROWSER_TEST_F ( PrefsFunctionalTest , TestHomepageNewTabpagePrefs ) {
 EXPECT_TRUE ( browser ( ) -> profile ( ) -> GetPrefs ( ) -> GetBoolean ( prefs : : kHomePageIsNewTabPage ) ) ;
 }