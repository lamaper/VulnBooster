TEST_F ( SSLErrorAssistantTest , DynamicInterstitialListCertErrorMismatch ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 EXPECT_EQ ( 1u , ssl_info ( ) . public_key_hashes . size ( ) ) ;
 auto config_proto = std : : make_unique < chrome_browser_ssl : : SSLErrorAssistantConfig > ( ) ;
 config_proto -> set_version_id ( kLargeVersionId ) ;
 chrome_browser_ssl : : DynamicInterstitial * filter = config_proto -> add_dynamic_interstitial ( ) ;
 filter -> set_interstitial_type ( chrome_browser_ssl : : DynamicInterstitial : : INTERSTITIAL_PAGE_SSL ) ;
 filter -> set_cert_error ( chrome_browser_ssl : : DynamicInterstitial : : ERR_CERT_DATE_INVALID ) ;
 filter -> add_sha256_hash ( "sha256uthatch" ) ;
 filter -> add_sha256_hash ( ssl_info ( ) . public_key_hashes [ 0 ] . ToString ( ) ) ;
 filter -> add_sha256_hash ( "sha256/treecreeper" ) ;
 filter -> set_issuer_common_name_regex ( issuer_common_name ( ) ) ;
 filter -> set_issuer_organization_regex ( issuer_organization_name ( ) ) ;
 filter -> set_mitm_software_name ( "UwS" ) ;
 error_assistant ( ) -> SetErrorAssistantProto ( std : : move ( config_proto ) ) ;
 EXPECT_FALSE ( error_assistant ( ) -> MatchDynamicInterstitial ( ssl_info ( ) ) ) ;
 }