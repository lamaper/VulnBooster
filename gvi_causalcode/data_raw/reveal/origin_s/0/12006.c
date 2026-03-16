TEST_F ( SSLErrorAssistantTest , DynamicInterstitialListNoCertHashes ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 EXPECT_EQ ( 1u , ssl_info ( ) . public_key_hashes . size ( ) ) ;
 auto config_proto = std : : make_unique < chrome_browser_ssl : : SSLErrorAssistantConfig > ( ) ;
 config_proto -> set_version_id ( kLargeVersionId ) ;
 chrome_browser_ssl : : DynamicInterstitial * filter = config_proto -> add_dynamic_interstitial ( ) ;
 filter -> set_interstitial_type ( chrome_browser_ssl : : DynamicInterstitial : : INTERSTITIAL_PAGE_CAPTIVE_PORTAL ) ;
 filter -> set_cert_error ( chrome_browser_ssl : : DynamicInterstitial : : UNKNOWN_CERT_ERROR ) ;
 filter -> add_sha256_hash ( "sha256ightjar" ) ;
 filter -> add_sha256_hash ( "sha256/frogmouth" ) ;
 filter -> add_sha256_hash ( "sha256/poorwill" ) ;
 filter = config_proto -> add_dynamic_interstitial ( ) ;
 filter -> set_interstitial_type ( chrome_browser_ssl : : DynamicInterstitial : : INTERSTITIAL_PAGE_SSL ) ;
 filter -> set_cert_error ( chrome_browser_ssl : : DynamicInterstitial : : ERR_CERT_COMMON_NAME_INVALID ) ;
 filter -> set_issuer_common_name_regex ( issuer_common_name ( ) ) ;
 filter -> set_issuer_organization_regex ( issuer_organization_name ( ) ) ;
 filter -> set_mitm_software_name ( "UwS" ) ;
 error_assistant ( ) -> SetErrorAssistantProto ( std : : move ( config_proto ) ) ;
 base : : Optional < DynamicInterstitialInfo > dynamic_interstitial = error_assistant ( ) -> MatchDynamicInterstitial ( ssl_info ( ) ) ;
 ASSERT_TRUE ( dynamic_interstitial ) ;
 EXPECT_EQ ( chrome_browser_ssl : : DynamicInterstitial : : INTERSTITIAL_PAGE_SSL , dynamic_interstitial -> interstitial_type ) ;
 }