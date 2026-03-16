IN_PROC_BROWSER_TEST_F ( LocalNTPOneGoogleBarSmokeTest , NTPLoadsWithoutErrorOnNetworkFailure ) {
 content : : WebContents * active_tab = local_ntp_test_utils : : OpenNewTab ( browser ( ) , GURL ( "about:blank" ) ) ;
 ASSERT_FALSE ( search : : IsInstantNTP ( active_tab ) ) ;
 content : : ConsoleObserverDelegate console_observer ( active_tab , "*" ) ;
 active_tab -> SetDelegate ( & console_observer ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , GURL ( chrome : : kChromeUINewTabURL ) ) ;
 ASSERT_TRUE ( search : : IsInstantNTP ( active_tab ) ) ;
 ASSERT_EQ ( GURL ( chrome : : kChromeSearchLocalNtpUrl ) , active_tab -> GetController ( ) . GetVisibleEntry ( ) -> GetURL ( ) ) ;
 EXPECT_TRUE ( console_observer . message ( ) . empty ( ) ) << console_observer . message ( ) ;
 }