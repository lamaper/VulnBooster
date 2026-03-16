TEST_F ( ProtocolHandlerRegistryTest , TestRemovingDefaultFallsBackToOldDefault ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "mailto" , "test1" ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "mailto" , "test2" ) ;
 ProtocolHandler ph3 = CreateProtocolHandler ( "mailto" , "test3" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph2 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph3 ) ;
 ASSERT_TRUE ( registry ( ) -> IsDefault ( ph3 ) ) ;
 registry ( ) -> RemoveHandler ( ph3 ) ;
 ASSERT_TRUE ( registry ( ) -> IsDefault ( ph2 ) ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph3 ) ;
 ASSERT_TRUE ( registry ( ) -> IsDefault ( ph3 ) ) ;
 registry ( ) -> RemoveHandler ( ph2 ) ;
 ASSERT_TRUE ( registry ( ) -> IsDefault ( ph3 ) ) ;
 registry ( ) -> RemoveHandler ( ph3 ) ;
 ASSERT_TRUE ( registry ( ) -> IsDefault ( ph1 ) ) ;
 }