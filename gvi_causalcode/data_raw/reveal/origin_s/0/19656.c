IN_PROC_BROWSER_TEST_F ( FastUnloadTest , DISABLED_WindowCloseFinishesUnload ) {
 NavigateToPage ( "no_listeners" ) ;
 EXPECT_EQ ( "unloaded=ohyeah" , GetCookies ( "no_listeners" ) ) ;
 }