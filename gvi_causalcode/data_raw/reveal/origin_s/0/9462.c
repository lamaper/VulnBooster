TEST_F ( ProtocolHandlerRegistryTest , TestMaybeCreateTaskWorksFromIOThread ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "mailto" , "test1" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 GURL url ( "mailto:someone@something.com" ) ;
 scoped_ptr < net : : URLRequestJobFactory > interceptor ( registry ( ) -> CreateJobInterceptorFactory ( ) ) ;
 AssertIntercepted ( url , interceptor . get ( ) ) ;
 }