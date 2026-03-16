TEST_F ( ProtocolHandlerRegistryTest , TestEnabledDisabled ) {
 registry ( ) -> Disable ( ) ;
 ASSERT_FALSE ( registry ( ) -> enabled ( ) ) ;
 registry ( ) -> Enable ( ) ;
 ASSERT_TRUE ( registry ( ) -> enabled ( ) ) ;
 }