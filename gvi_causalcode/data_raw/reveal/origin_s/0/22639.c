IN_PROC_BROWSER_TEST_F ( PrefsFunctionalTest , TestJavascriptEnableDisable ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 EXPECT_TRUE ( browser ( ) -> profile ( ) -> GetPrefs ( ) -> GetBoolean ( prefs : : kWebKitJavascriptEnabled ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/javaScriptTitle.html" ) ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "Title from script javascript enabled" ) , browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) -> GetTitle ( ) ) ;
 browser ( ) -> profile ( ) -> GetPrefs ( ) -> SetBoolean ( prefs : : kWebKitJavascriptEnabled , false ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/javaScriptTitle.html" ) ) ;
 EXPECT_EQ ( base : : ASCIIToUTF16 ( "This is html title" ) , browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) -> GetTitle ( ) ) ;
 }