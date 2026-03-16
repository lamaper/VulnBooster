TEST_F ( ProtocolHandlerRegistryTest , TestOSRegistration ) {
 ProtocolHandler ph_do1 = CreateProtocolHandler ( "do" , "test1" ) ;
 ProtocolHandler ph_do2 = CreateProtocolHandler ( "do" , "test2" ) ;
 ProtocolHandler ph_dont = CreateProtocolHandler ( "dont" , "test" ) ;
 ASSERT_FALSE ( delegate ( ) -> IsFakeRegisteredWithOS ( "do" ) ) ;
 ASSERT_FALSE ( delegate ( ) -> IsFakeRegisteredWithOS ( "dont" ) ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph_do1 ) ;
 registry ( ) -> OnDenyRegisterProtocolHandler ( ph_dont ) ;
 base : : MessageLoop : : current ( ) -> Run ( ) ;
 ASSERT_TRUE ( delegate ( ) -> IsFakeRegisteredWithOS ( "do" ) ) ;
 ASSERT_FALSE ( delegate ( ) -> IsFakeRegisteredWithOS ( "dont" ) ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph_do2 ) ;
 }