IN_PROC_BROWSER_TEST_P ( SupervisedUserNavigationThrottleNotSupervisedTest , DontBlock ) {
 BlockHost ( kExampleHost ) ;
 GURL blocked_url = embedded_test_server ( ) -> GetURL ( kExampleHost , "/supervised_user/simple.html" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , blocked_url ) ;
 EXPECT_FALSE ( IsInterstitialBeingShown ( browser ( ) ) ) ;
 }