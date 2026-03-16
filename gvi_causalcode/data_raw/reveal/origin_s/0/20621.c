IN_PROC_BROWSER_TEST_P ( SupervisedUserNavigationThrottleTest , BlockMainFrameWithInterstitial ) {
 BlockHost ( kExampleHost2 ) ;
 GURL allowed_url = embedded_test_server ( ) -> GetURL ( kExampleHost , "/supervised_user/simple.html" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , allowed_url ) ;
 EXPECT_FALSE ( IsInterstitialBeingShown ( browser ( ) ) ) ;
 GURL blocked_url = embedded_test_server ( ) -> GetURL ( kExampleHost2 , "/supervised_user/simple.html" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , blocked_url ) ;
 EXPECT_TRUE ( IsInterstitialBeingShown ( browser ( ) ) ) ;
 }