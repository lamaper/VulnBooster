TEST_F ( ProtocolHandlerRegistryTest , TestLoadEnabledGetsPropogatedToIO ) {
 std : : string mailto ( "mailto" ) ;
 ProtocolHandler ph1 = CreateProtocolHandler ( mailto , "MailtoHandler" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 scoped_ptr < ProtocolHandlerRegistry : : JobInterceptorFactory > interceptor ( registry ( ) -> CreateJobInterceptorFactory ( ) ) ;
 AssertWillHandle ( mailto , true , interceptor . get ( ) ) ;
 registry ( ) -> Disable ( ) ;
 AssertWillHandle ( mailto , false , interceptor . get ( ) ) ;
 }