IN_PROC_BROWSER_TEST_F ( ExternalProtocolDialogBrowserTest , TestCancel ) {
 ShowDialog ( ) ;
 EXPECT_TRUE ( dialog_ -> Cancel ( ) ) ;
 EXPECT_TRUE ( called_ ) ;
 EXPECT_FALSE ( accept_ ) ;
 EXPECT_TRUE ( cancel_ ) ;
 EXPECT_FALSE ( dont_block_ ) ;
 histogram_tester_ . ExpectBucketCount ( ExternalProtocolHandler : : kRememberCheckboxMetric , 0 , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( ExternalProtocolHandler : : kHandleStateMetric , ExternalProtocolHandler : : DONT_LAUNCH , 1 ) ;
 }