TEST_F ( ProtocolHandlerRegistryTest , TestReplaceRemovesStaleHandlers ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "mailto" , GURL ( "http://test.com/%s" ) , "test1" ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "mailto" , GURL ( "http://test.com/updated-url/%s" ) , "test2" ) ;
 ProtocolHandler ph3 = CreateProtocolHandler ( "mailto" , GURL ( "http://test.com/third/%s" ) , "test" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph2 ) ;
 ASSERT_TRUE ( registry ( ) -> AttemptReplace ( ph3 ) ) ;
 const ProtocolHandler & handler ( registry ( ) -> GetHandlerFor ( "mailto" ) ) ;
 ASSERT_EQ ( handler . url ( ) , ph3 . url ( ) ) ;
 registry ( ) -> RemoveHandler ( ph3 ) ;
 ASSERT_TRUE ( registry ( ) -> GetHandlerFor ( "mailto" ) . IsEmpty ( ) ) ;
 }