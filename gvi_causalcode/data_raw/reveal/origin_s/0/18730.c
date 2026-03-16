IN_PROC_BROWSER_TEST_F ( ExternalProtocolDialogBrowserTest , TestAccept ) {
 ShowDialog ( ) ;
 EXPECT_TRUE ( dialog_ -> Accept ( ) ) ;
 EXPECT_TRUE ( called_ ) ;
 EXPECT_TRUE ( accept_ ) ;
 EXPECT_FALSE ( remember_ ) ;
 histogram_tester_ . ExpectBucketCount ( ExternalProtocolHandler : : kHandleStateMetric , ExternalProtocolHandler : : LAUNCH , 1 ) ;
 }