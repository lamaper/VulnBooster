TEST_F ( SSLErrorAssistantTest , DynamicInterstitialListMatchBlank ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 EXPECT_EQ ( 1u , ssl_info ( ) . public_key_hashes . size ( ) ) ;
 auto config_proto = std : : make_unique < chrome_browser_ssl : : SSLErrorAssistantConfig > ( ) ;
 config_proto -> set_version_id ( kLargeVersionId ) ;
 chrome_browser_ssl : : DynamicInterstitial * filter = config_proto -> add_dynamic_interstitial ( ) ;
 filter -> set_interstitial_type ( chrome_browser_ssl : : DynamicInterstitial : : INTERSTITIAL_PAGE_SSL ) ;
 error_assistant ( ) -> SetErrorAssistantProto ( std : : move ( config_proto ) ) ;
 base : : Optional < DynamicInterstitialInfo > dynamic_interstitial = error_assistant ( ) -> MatchDynamicInterstitial ( ssl_info ( ) ) ;
 ASSERT_TRUE ( dynamic_interstitial ) ;
 EXPECT_EQ ( chrome_browser_ssl : : DynamicInterstitial : : INTERSTITIAL_PAGE_SSL , dynamic_interstitial -> interstitial_type ) ;
 }