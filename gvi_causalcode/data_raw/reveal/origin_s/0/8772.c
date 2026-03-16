TEST_F ( SSLErrorAssistantTest , MitMSoftwareMatching ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto config_proto = std : : make_unique < chrome_browser_ssl : : SSLErrorAssistantConfig > ( ) ;
 config_proto -> set_version_id ( kLargeVersionId ) ;
 chrome_browser_ssl : : MITMSoftware * filter = config_proto -> add_mitm_software ( ) ;
 filter -> set_name ( "Basic Check" ) ;
 filter -> set_issuer_common_name_regex ( "Misconfig Software" ) ;
 filter -> set_issuer_organization_regex ( "Test Company" ) ;
 filter = config_proto -> add_mitm_software ( ) ;
 filter -> set_name ( "Regex Check" ) ;
 filter -> set_issuer_common_name_regex ( "ij[a-z]+n opqrs" ) ;
 filter -> set_issuer_organization_regex ( "abc de[a-z0-9]gh [a-z]+" ) ;
 error_assistant ( ) -> SetErrorAssistantProto ( std : : move ( config_proto ) ) ;
 TestMITMSoftwareMatchFromString ( kMisconfigSoftwareCert , "Basic Check" ) ;
 TestMITMSoftwareMatchFromString ( kMisconfigSoftwareRegexCheckCert , "Regex Check" ) ;
 error_assistant ( ) -> ResetForTesting ( ) ;
 config_proto . reset ( new chrome_browser_ssl : : SSLErrorAssistantConfig ( ) ) ;
 config_proto -> set_version_id ( kLargeVersionId ) ;
 filter = config_proto -> add_mitm_software ( ) ;
 filter -> set_name ( "Incorrect common name" ) ;
 filter -> set_issuer_common_name_regex ( "Misconfig Sotware" ) ;
 filter -> set_issuer_organization_regex ( "Test Company" ) ;
 filter = config_proto -> add_mitm_software ( ) ;
 filter -> set_name ( "Incorrect company name" ) ;
 filter -> set_issuer_common_name_regex ( "Misconfig Software" ) ;
 filter -> set_issuer_organization_regex ( "Tst Company" ) ;
 error_assistant ( ) -> SetErrorAssistantProto ( std : : move ( config_proto ) ) ;
 TestMITMSoftwareMatchFromString ( kMisconfigSoftwareCert , "" ) ;
 }