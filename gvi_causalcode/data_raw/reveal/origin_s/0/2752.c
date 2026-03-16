TEST_F ( ProtocolHandlerRegistryTest , TestGetHandlersFor ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , "test1" ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "test" , "test2" ) ;
 ProtocolHandler ph3 = CreateProtocolHandler ( "test" , "test3" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph2 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph3 ) ;
 ProtocolHandlerRegistry : : ProtocolHandlerList handlers = registry ( ) -> GetHandlersFor ( "test" ) ;
 ASSERT_EQ ( static_cast < size_t > ( 3 ) , handlers . size ( ) ) ;
 ASSERT_EQ ( ph3 , handlers [ 0 ] ) ;
 ASSERT_EQ ( ph2 , handlers [ 1 ] ) ;
 ASSERT_EQ ( ph1 , handlers [ 2 ] ) ;
 }