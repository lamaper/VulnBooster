TEST_F ( SSLErrorAssistantTest , CaptivePortalCertificateList ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 EXPECT_EQ ( 1u , ssl_info ( ) . public_key_hashes . size ( ) ) ;
 auto config_proto = std : : make_unique < chrome_browser_ssl : : SSLErrorAssistantConfig > ( ) ;
 config_proto -> set_version_id ( kLargeVersionId ) ;
 config_proto -> add_captive_portal_cert ( ) -> set_sha256_hash ( "sha256/boxfish" ) ;
 config_proto -> add_captive_portal_cert ( ) -> set_sha256_hash ( "sha256/treecreeper" ) ;
 error_assistant ( ) -> SetErrorAssistantProto ( std : : move ( config_proto ) ) ;
 EXPECT_FALSE ( error_assistant ( ) -> IsKnownCaptivePortalCertificate ( ssl_info ( ) ) ) ;
 error_assistant ( ) -> ResetForTesting ( ) ;
 config_proto . reset ( new chrome_browser_ssl : : SSLErrorAssistantConfig ( ) ) ;
 config_proto -> set_version_id ( kLargeVersionId ) ;
 config_proto -> add_captive_portal_cert ( ) -> set_sha256_hash ( "sha256/boxfish" ) ;
 config_proto -> add_captive_portal_cert ( ) -> set_sha256_hash ( ssl_info ( ) . public_key_hashes [ 0 ] . ToString ( ) ) ;
 config_proto -> add_captive_portal_cert ( ) -> set_sha256_hash ( "sha256/treecreeper" ) ;
 error_assistant ( ) -> SetErrorAssistantProto ( std : : move ( config_proto ) ) ;
 EXPECT_TRUE ( error_assistant ( ) -> IsKnownCaptivePortalCertificate ( ssl_info ( ) ) ) ;
 }