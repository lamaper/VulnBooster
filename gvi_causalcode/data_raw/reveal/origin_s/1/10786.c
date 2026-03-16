void xsltCompileAttr ( xsltStylesheetPtr style , xmlAttrPtr attr ) {
 const xmlChar * str ;
 const xmlChar * cur ;
 xmlChar * ret = NULL ;
 xmlChar * expr = NULL ;
 xsltAttrVTPtr avt ;
 int i = 0 , lastavt = 0 ;
 if ( ( style == NULL ) || ( attr == NULL ) || ( attr -> children == NULL ) ) return ;
 if ( ( attr -> children -> type != XML_TEXT_NODE ) || ( attr -> children -> next != NULL ) ) {
 xsltTransformError ( NULL , style , attr -> parent , "Attribute '%s': The content is expected to be a single text " "node when compiling an AVT.\n" , attr -> name ) ;
 style -> errors ++ ;
 return ;
 }
 str = attr -> children -> content ;
 if ( ( xmlStrchr ( str , '{
' ) == NULL ) && ( xmlStrchr ( str , '}
' ) == NULL ) ) return ;




 }
 avt = xsltNewAttrVT ( style ) ;
 if ( avt == NULL ) return ;
 attr -> psvi = avt ;
 avt -> nsList = xmlGetNsList ( attr -> doc , attr -> parent ) ;
 if ( avt -> nsList != NULL ) {
 while ( avt -> nsList [ i ] != NULL ) i ++ ;
 }
 avt -> nsNr = i ;
 cur = str ;
 while ( * cur != 0 ) {
 if ( * cur == '{
' ) {
 if ( * ( cur + 1 ) == '{
' ) {
 cur ++ ;
 ret = xmlStrncat ( ret , str , cur - str ) ;
 cur ++ ;
 str = cur ;
 continue ;
 }
 if ( * ( cur + 1 ) == '}
' ) {
 ret = xmlStrncat ( ret , str , cur - str ) ;
 cur += 2 ;
 str = cur ;
 continue ;
 }
 if ( ( ret != NULL ) || ( cur - str > 0 ) ) {
 ret = xmlStrncat ( ret , str , cur - str ) ;
 str = cur ;
 if ( avt -> nb_seg == 0 ) avt -> strstart = 1 ;
 if ( ( avt = xsltSetAttrVTsegment ( avt , ( void * ) ret ) ) == NULL ) goto error ;
 ret = NULL ;
 lastavt = 0 ;
 }
 cur ++ ;
 while ( ( * cur != 0 ) && ( * cur != '}
' ) ) {
 if ( ( * cur == '\'' ) || ( * cur == '"' ) ) {
 char delim = * ( cur ++ ) ;
 while ( ( * cur != 0 ) && ( * cur != delim ) ) cur ++ ;
 if ( * cur != 0 ) cur ++ ;
 }
 else cur ++ ;
 }
 if ( * cur == 0 ) {
 xsltTransformError ( NULL , style , attr -> parent , "Attribute '%s': The AVT has an unmatched '{
'.\n" , attr -> name ) ;
 style -> errors ++ ;
 goto error ;
 }
 str ++ ;
 expr = xmlStrndup ( str , cur - str ) ;
 if ( expr == NULL ) {
 XSLT_TODO goto error ;
 }
 else {
 xmlXPathCompExprPtr comp ;
 comp = xsltXPathCompile ( style , expr ) ;
 if ( comp == NULL ) {
 xsltTransformError ( NULL , style , attr -> parent , "Attribute '%s': Failed to compile the expression " "'%s' in the AVT.\n" , attr -> name , expr ) ;
 style -> errors ++ ;
 goto error ;
 }
 if ( avt -> nb_seg == 0 ) avt -> strstart = 0 ;
 if ( lastavt == 1 ) {
 if ( ( avt = xsltSetAttrVTsegment ( avt , NULL ) ) == NULL ) goto error ;
 }
 if ( ( avt = xsltSetAttrVTsegment ( avt , ( void * ) comp ) ) == NULL ) goto error ;
 lastavt = 1 ;
 xmlFree ( expr ) ;
 expr = NULL ;
 }
 cur ++ ;
 str = cur ;
 }
 else if ( * cur == '}
' ) {
 cur ++ ;
 if ( * cur == '}
' ) {
 ret = xmlStrncat ( ret , str , cur - str ) ;
 cur ++ ;
 str = cur ;
 continue ;
 }
 else {
 xsltTransformError ( NULL , style , attr -> parent , "Attribute '%s': The AVT has an unmatched '}
'.\n" , attr -> name ) ;
 goto error ;
 }
 }
 else cur ++ ;
 }
 if ( ( ret != NULL ) || ( cur - str > 0 ) ) {
 ret = xmlStrncat ( ret , str , cur - str ) ;
 str = cur ;
 if ( avt -> nb_seg == 0 ) avt -> strstart = 1 ;
 if ( ( avt = xsltSetAttrVTsegment ( avt , ( void * ) ret ) ) == NULL ) goto error ;
 ret = NULL ;
 }
 error : if ( avt == NULL ) {
 xsltTransformError ( NULL , style , attr -> parent , "xsltCompileAttr: malloc problem\n" ) ;
 }
 else {
 if ( attr -> psvi != avt ) {
 attr -> psvi = avt ;
 style -> attVTs = avt ;
 }
 }
 if ( ret != NULL ) xmlFree ( ret ) ;
 if ( expr != NULL ) xmlFree ( expr ) ;
 }