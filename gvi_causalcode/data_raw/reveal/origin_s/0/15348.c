TEST_F ( ProtocolHandlerRegistryTest , MAYBE_TestIsHandledProtocolWorksOnIOThread ) {
 std : : string scheme ( "mailto" ) ;
 ProtocolHandler ph1 = CreateProtocolHandler ( scheme , "test1" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 scoped_ptr < ProtocolHandlerRegistry : : JobInterceptorFactory > interceptor ( registry ( ) -> CreateJobInterceptorFactory ( ) ) ;
 AssertWillHandle ( scheme , true , interceptor . get ( ) ) ;
 }