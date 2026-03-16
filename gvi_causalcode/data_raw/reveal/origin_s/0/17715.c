TEST_F ( ProtocolHandlerRegistryTest , TestReplaceHandler ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "mailto" , GURL ( "http://test.com/%s" ) ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "mailto" , GURL ( "http://test.com/updated-url/%s" ) ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 ASSERT_TRUE ( registry ( ) -> AttemptReplace ( ph2 ) ) ;
 const ProtocolHandler & handler ( registry ( ) -> GetHandlerFor ( "mailto" ) ) ;
 ASSERT_EQ ( handler . url ( ) , ph2 . url ( ) ) ;
 }