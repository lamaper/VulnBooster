TEST_F ( ProtocolHandlerRegistryTest , TestReplaceNonDefaultHandler ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "mailto" , GURL ( "http://test.com/%s" ) , "test1" ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "mailto" , GURL ( "http://test.com/updated-url/%s" ) , "test2" ) ;
 ProtocolHandler ph3 = CreateProtocolHandler ( "mailto" , GURL ( "http://else.com/%s" ) , "test3" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph3 ) ;
 ASSERT_TRUE ( registry ( ) -> AttemptReplace ( ph2 ) ) ;
 const ProtocolHandler & handler ( registry ( ) -> GetHandlerFor ( "mailto" ) ) ;
 ASSERT_EQ ( handler . url ( ) , ph3 . url ( ) ) ;
 }