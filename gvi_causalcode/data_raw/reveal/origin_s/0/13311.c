TEST_F ( ProtocolHandlerRegistryTest , TestDefaultSaveLoad ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , "test1" ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "test" , "test2" ) ;
 registry ( ) -> OnDenyRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> OnDenyRegisterProtocolHandler ( ph2 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph2 ) ;
 registry ( ) -> Disable ( ) ;
 RecreateRegistry ( true ) ;
 ASSERT_FALSE ( registry ( ) -> enabled ( ) ) ;
 registry ( ) -> Enable ( ) ;
 ASSERT_FALSE ( registry ( ) -> IsDefault ( ph1 ) ) ;
 ASSERT_TRUE ( registry ( ) -> IsDefault ( ph2 ) ) ;
 RecreateRegistry ( true ) ;
 ASSERT_TRUE ( registry ( ) -> enabled ( ) ) ;
 }