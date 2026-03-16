TEST_F ( ProtocolHandlerRegistryTest , TestReplaceHandler ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "mailto" , GURL ( "http://test.com/%s" ) , "test1" ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "mailto" , GURL ( "http://test.com/updated-url/%s" ) , "test2" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 ASSERT_TRUE ( registry ( ) -> AttemptReplace ( ph2 ) ) ;
 const ProtocolHandler & handler ( registry ( ) -> GetHandlerFor ( "mailto" ) ) ;
 ASSERT_EQ ( handler . url ( ) , ph2 . url ( ) ) ;
 }