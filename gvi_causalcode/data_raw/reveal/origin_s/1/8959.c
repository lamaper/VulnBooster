IN_PROC_BROWSER_TEST_F ( ExternalProtocolDialogBrowserTest , TestCancelWithChecked ) {
 ShowDialog ( ) ;
 SetChecked ( true ) ;
 EXPECT_TRUE ( dialog_ -> Cancel ( ) ) ;
 EXPECT_TRUE ( called_ ) ;
 EXPECT_FALSE ( accept_ ) ;
 EXPECT_TRUE ( cancel_ ) ;
 EXPECT_TRUE ( dont_block_ ) ;
 histogram_tester_ . ExpectBucketCount ( ExternalProtocolHandler : : kRememberCheckboxMetric , 1 , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( ExternalProtocolHandler : : kHandleStateMetric , ExternalProtocolHandler : : CHECKED_DONT_LAUNCH , 1 ) ;
 }