void xsltDebug ( xsltTransformContextPtr ctxt , xmlNodePtr node ATTRIBUTE_UNUSED , xmlNodePtr inst ATTRIBUTE_UNUSED , xsltStylePreCompPtr comp ATTRIBUTE_UNUSED ) {
 int i , j ;
 xsltGenericError ( xsltGenericErrorContext , "Templates:\n" ) ;
 for ( i = 0 , j = ctxt -> templNr - 1 ;
 ( ( i < 15 ) && ( j >= 0 ) ) ;
 i ++ , j -- ) {
 xsltGenericError ( xsltGenericErrorContext , "#%d " , i ) ;
 if ( ctxt -> templTab [ j ] -> name != NULL ) xsltGenericError ( xsltGenericErrorContext , "name %s " , ctxt -> templTab [ j ] -> name ) ;
 if ( ctxt -> templTab [ j ] -> match != NULL ) xsltGenericError ( xsltGenericErrorContext , "name %s " , ctxt -> templTab [ j ] -> match ) ;
 if ( ctxt -> templTab [ j ] -> mode != NULL ) xsltGenericError ( xsltGenericErrorContext , "name %s " , ctxt -> templTab [ j ] -> mode ) ;
 xsltGenericError ( xsltGenericErrorContext , "\n" ) ;
 }
 xsltGenericError ( xsltGenericErrorContext , "Variables:\n" ) ;
 for ( i = 0 , j = ctxt -> varsNr - 1 ;
 ( ( i < 15 ) && ( j >= 0 ) ) ;
 i ++ , j -- ) {
 xsltStackElemPtr cur ;
 if ( ctxt -> varsTab [ j ] == NULL ) continue ;
 xsltGenericError ( xsltGenericErrorContext , "#%d\n" , i ) ;
 cur = ctxt -> varsTab [ j ] ;
 while ( cur != NULL ) {
 if ( cur -> comp == NULL ) {
 xsltGenericError ( xsltGenericErrorContext , "corrupted !!!\n" ) ;
 }
 else if ( cur -> comp -> type == XSLT_FUNC_PARAM ) {
 xsltGenericError ( xsltGenericErrorContext , "param " ) ;
 }
 else if ( cur -> comp -> type == XSLT_FUNC_VARIABLE ) {
 xsltGenericError ( xsltGenericErrorContext , "var " ) ;
 }
 if ( cur -> name != NULL ) xsltGenericError ( xsltGenericErrorContext , "%s " , cur -> name ) ;
 else xsltGenericError ( xsltGenericErrorContext , "noname !!!!" ) ;

 xmlXPathDebugDumpObject ( stdout , cur -> value , 1 ) ;
 }
 else {
 xsltGenericError ( xsltGenericErrorContext , "NULL !!!!" ) ;
 }

 cur = cur -> next ;
 }
 }
 }