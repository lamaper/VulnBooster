TEST_F ( ProtocolHandlerRegistryTest , MAYBE_TestOSRegistrationFailure ) {
 ProtocolHandler ph_do = CreateProtocolHandler ( "do" , "test1" ) ;
 ProtocolHandler ph_dont = CreateProtocolHandler ( "dont" , "test" ) ;
 ASSERT_FALSE ( registry ( ) -> IsHandledProtocol ( "do" ) ) ;
 ASSERT_FALSE ( registry ( ) -> IsHandledProtocol ( "dont" ) ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph_do ) ;
 base : : MessageLoop : : current ( ) -> Run ( ) ;
 delegate ( ) -> set_force_os_failure ( true ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph_dont ) ;
 base : : MessageLoop : : current ( ) -> Run ( ) ;
 ASSERT_TRUE ( registry ( ) -> IsHandledProtocol ( "do" ) ) ;
 ASSERT_EQ ( static_cast < size_t > ( 1 ) , registry ( ) -> GetHandlersFor ( "do" ) . size ( ) ) ;
 ASSERT_FALSE ( registry ( ) -> IsHandledProtocol ( "dont" ) ) ;
 ASSERT_EQ ( static_cast < size_t > ( 1 ) , registry ( ) -> GetHandlersFor ( "dont" ) . size ( ) ) ;
 }