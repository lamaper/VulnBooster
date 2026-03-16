TEST_F ( ProtocolHandlerRegistryTest , TestRemovingDefaultDoesntChangeHandlers ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "mailto" , "test1" ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "mailto" , "test2" ) ;
 ProtocolHandler ph3 = CreateProtocolHandler ( "mailto" , "test3" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph2 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph3 ) ;
 registry ( ) -> RemoveHandler ( ph3 ) ;
 ProtocolHandlerRegistry : : ProtocolHandlerList handlers = registry ( ) -> GetHandlersFor ( "mailto" ) ;
 ASSERT_EQ ( static_cast < size_t > ( 2 ) , handlers . size ( ) ) ;
 ASSERT_EQ ( ph2 , handlers [ 0 ] ) ;
 ASSERT_EQ ( ph1 , handlers [ 1 ] ) ;
 }