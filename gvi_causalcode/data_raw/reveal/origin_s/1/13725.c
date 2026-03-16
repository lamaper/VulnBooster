IN_PROC_BROWSER_TEST_F ( SupervisedUserNavigationThrottleNotSupervisedTest , DontBlock ) {
 BlockHost ( kExampleHost ) ;
 WebContents * tab = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 GURL blocked_url = embedded_test_server ( ) -> GetURL ( kExampleHost , "/supervised_user/simple.html" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , blocked_url ) ;
 EXPECT_FALSE ( tab -> ShowingInterstitialPage ( ) ) ;
 }