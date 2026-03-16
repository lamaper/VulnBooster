TEST_F ( ProtocolHandlerRegistryTest , TestSilentlyRegisterHandler ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , GURL ( "http://test/1/%s" ) ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "test" , GURL ( "http://test/2/%s" ) ) ;
 ProtocolHandler ph3 = CreateProtocolHandler ( "ignore" , GURL ( "http://test/%s" ) ) ;
 ProtocolHandler ph4 = CreateProtocolHandler ( "ignore" , GURL ( "http://test/%s" ) ) ;
 ASSERT_FALSE ( registry ( ) -> SilentlyHandleRegisterHandlerRequest ( ph1 ) ) ;
 ASSERT_FALSE ( registry ( ) -> IsRegistered ( ph1 ) ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 ASSERT_TRUE ( registry ( ) -> IsRegistered ( ph1 ) ) ;
 ASSERT_TRUE ( registry ( ) -> SilentlyHandleRegisterHandlerRequest ( ph2 ) ) ;
 ASSERT_FALSE ( registry ( ) -> IsRegistered ( ph1 ) ) ;
 ASSERT_TRUE ( registry ( ) -> IsRegistered ( ph2 ) ) ;
 ASSERT_FALSE ( registry ( ) -> SilentlyHandleRegisterHandlerRequest ( ph3 ) ) ;
 ASSERT_FALSE ( registry ( ) -> IsRegistered ( ph3 ) ) ;
 registry ( ) -> OnIgnoreRegisterProtocolHandler ( ph3 ) ;
 ASSERT_FALSE ( registry ( ) -> IsRegistered ( ph3 ) ) ;
 ASSERT_TRUE ( registry ( ) -> IsIgnored ( ph3 ) ) ;
 ASSERT_TRUE ( registry ( ) -> SilentlyHandleRegisterHandlerRequest ( ph4 ) ) ;
 ASSERT_FALSE ( registry ( ) -> IsRegistered ( ph4 ) ) ;
 ASSERT_TRUE ( registry ( ) -> HasIgnoredEquivalent ( ph4 ) ) ;
 }