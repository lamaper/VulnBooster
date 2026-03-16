IN_PROC_BROWSER_TEST_F ( PrefsFunctionalTest , TestHaveLocalStatePrefs ) {
 EXPECT_TRUE ( g_browser_process -> local_state ( ) -> GetPreferenceValues ( PrefService : : INCLUDE_DEFAULTS ) . get ( ) ) ;
 }