IN_PROC_BROWSER_TEST_F ( ExternalProtocolDialogBrowserTest , TestAcceptWithChecked ) {
 ShowDialog ( ) ;
 SetChecked ( true ) ;
 EXPECT_TRUE ( dialog_ -> Accept ( ) ) ;
 EXPECT_TRUE ( called_ ) ;
 EXPECT_TRUE ( accept_ ) ;
 EXPECT_FALSE ( cancel_ ) ;
 EXPECT_TRUE ( dont_block_ ) ;
 histogram_tester_ . ExpectBucketCount ( ExternalProtocolHandler : : kRememberCheckboxMetric , 1 , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( ExternalProtocolHandler : : kHandleStateMetric , ExternalProtocolHandler : : CHECKED_LAUNCH , 1 ) ;
 }