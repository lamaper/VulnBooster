IN_PROC_BROWSER_TEST_F ( SupervisedUserNavigationThrottleTest , BlockMainFrameWithInterstitial ) {
 BlockHost ( kExampleHost2 ) ;
 WebContents * tab = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 GURL allowed_url = embedded_test_server ( ) -> GetURL ( kExampleHost , "/supervised_user/simple.html" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , allowed_url ) ;
 EXPECT_FALSE ( tab -> ShowingInterstitialPage ( ) ) ;
 GURL blocked_url = embedded_test_server ( ) -> GetURL ( kExampleHost2 , "/supervised_user/simple.html" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , blocked_url ) ;
 EXPECT_TRUE ( tab -> ShowingInterstitialPage ( ) ) ;
 }