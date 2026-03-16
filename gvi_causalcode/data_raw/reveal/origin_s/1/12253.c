IN_PROC_BROWSER_TEST_F ( ExternalProtocolDialogBrowserTest , TestClose ) {
 ShowDialog ( ) ;
 EXPECT_TRUE ( dialog_ -> Close ( ) ) ;
 EXPECT_TRUE ( called_ ) ;
 EXPECT_FALSE ( accept_ ) ;
 EXPECT_TRUE ( cancel_ ) ;
 EXPECT_FALSE ( dont_block_ ) ;
 histogram_tester_ . ExpectTotalCount ( ExternalProtocolHandler : : kRememberCheckboxMetric , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( ExternalProtocolHandler : : kHandleStateMetric , 0 ) ;
 }