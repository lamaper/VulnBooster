IN_PROC_BROWSER_TEST_F ( ExternalProtocolDialogBrowserTest , TestCancel ) {
 ShowDialog ( ) ;
 EXPECT_TRUE ( dialog_ -> Cancel ( ) ) ;
 EXPECT_FALSE ( called_ ) ;
 EXPECT_FALSE ( accept_ ) ;
 EXPECT_FALSE ( remember_ ) ;
 histogram_tester_ . ExpectBucketCount ( ExternalProtocolHandler : : kHandleStateMetric , ExternalProtocolHandler : : DONT_LAUNCH , 1 ) ;
 }