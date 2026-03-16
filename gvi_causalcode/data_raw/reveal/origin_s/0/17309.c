TEST_F ( ProtocolHandlerRegistryTest , MAYBE_TestClearDefaultGetsPropagatedToIO ) {
 std : : string scheme ( "mailto" ) ;
 ProtocolHandler ph1 = CreateProtocolHandler ( scheme , "test1" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> ClearDefault ( scheme ) ;
 scoped_ptr < ProtocolHandlerRegistry : : JobInterceptorFactory > interceptor ( registry ( ) -> CreateJobInterceptorFactory ( ) ) ;
 AssertWillHandle ( scheme , false , interceptor . get ( ) ) ;
 }