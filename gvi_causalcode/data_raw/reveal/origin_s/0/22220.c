IN_PROC_BROWSER_TEST_F ( ExtensionPreferenceApiTest , DataReductionProxy ) {
 EXPECT_TRUE ( RunExtensionTest ( "preference/data_reduction_proxy" ) ) << message_ ;
 }