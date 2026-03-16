IN_PROC_BROWSER_TEST_F ( SupervisedUserNavigationThrottleTest , DontBlockSubFrame ) {
 BlockHost ( kExampleHost2 ) ;
 BlockHost ( kIframeHost2 ) ;
 WebContents * tab = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 GURL allowed_url_with_iframes = embedded_test_server ( ) -> GetURL ( kExampleHost , "/supervised_user/with_iframes.html" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , allowed_url_with_iframes ) ;
 EXPECT_FALSE ( tab -> ShowingInterstitialPage ( ) ) ;
 bool loaded1 = false ;
 ASSERT_TRUE ( content : : ExecuteScriptAndExtractBool ( tab , "loaded1()" , & loaded1 ) ) ;
 EXPECT_TRUE ( loaded1 ) ;
 bool loaded2 = false ;
 ASSERT_TRUE ( content : : ExecuteScriptAndExtractBool ( tab , "loaded2()" , & loaded2 ) ) ;
 EXPECT_TRUE ( loaded2 ) ;
 }