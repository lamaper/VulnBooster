IN_PROC_BROWSER_TEST_F ( LocalNTPOneGoogleBarSmokeTest , NTPLoadsWithOneGoogleBar ) {
 OneGoogleBarData data ;
 data . bar_html = "<div id='thebar'></div>" ;
 data . in_head_script = "window.inHeadRan = true;
" ;
 data . after_bar_script = "window.afterBarRan = true;
" ;
 data . end_of_body_script = "console.log('ogb-done');
" ;
 one_google_bar_fetcher ( ) -> set_one_google_bar_data ( data ) ;
 content : : WebContents * active_tab = local_ntp_test_utils : : OpenNewTab ( browser ( ) , GURL ( "about:blank" ) ) ;
 ASSERT_FALSE ( search : : IsInstantNTP ( active_tab ) ) ;
 content : : ConsoleObserverDelegate console_observer ( active_tab , "ogb-done" ) ;
 active_tab -> SetDelegate ( & console_observer ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , GURL ( chrome : : kChromeUINewTabURL ) ) ;
 ASSERT_TRUE ( search : : IsInstantNTP ( active_tab ) ) ;
 ASSERT_EQ ( GURL ( chrome : : kChromeSearchLocalNtpUrl ) , active_tab -> GetController ( ) . GetVisibleEntry ( ) -> GetURL ( ) ) ;
 console_observer . Wait ( ) ;
 EXPECT_EQ ( "ogb-done" , console_observer . message ( ) ) ;
 bool in_head_ran = false ;
 ASSERT_TRUE ( instant_test_utils : : GetBoolFromJS ( active_tab , "!!window.inHeadRan" , & in_head_ran ) ) ;
 EXPECT_TRUE ( in_head_ran ) ;
 bool after_bar_ran = false ;
 ASSERT_TRUE ( instant_test_utils : : GetBoolFromJS ( active_tab , "!!window.afterBarRan" , & after_bar_ran ) ) ;
 EXPECT_TRUE ( after_bar_ran ) ;
 }