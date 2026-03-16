IN_PROC_BROWSER_TEST_F ( RegisterProtocolHandlerBrowserTest , ContextMenuEntryAppearsForHandledUrls ) {
 scoped_ptr < TestRenderViewContextMenu > menu ( CreateContextMenu ( GURL ( "http://www.google.com/" ) ) ) ;
 ASSERT_FALSE ( menu -> IsItemPresent ( IDC_CONTENT_CONTEXT_OPENLINKWITH ) ) ;
 AddProtocolHandler ( std : : string ( "web+search" ) , GURL ( "http://www.google.com/%s" ) , base : : UTF8ToUTF16 ( std : : string ( "Test handler" ) ) ) ;
 GURL url ( "web+search:testing" ) ;
 ProtocolHandlerRegistry * registry = ProtocolHandlerRegistryFactory : : GetForProfile ( browser ( ) -> profile ( ) ) ;
 ASSERT_EQ ( 1u , registry -> GetHandlersFor ( url . scheme ( ) ) . size ( ) ) ;
 menu . reset ( CreateContextMenu ( url ) ) ;
 ASSERT_TRUE ( menu -> IsItemPresent ( IDC_CONTENT_CONTEXT_OPENLINKWITH ) ) ;
 }