static xmlDocPtr xsltDocDefaultLoaderFunc ( const xmlChar * URI , xmlDictPtr dict , int options , void * ctxt ATTRIBUTE_UNUSED , xsltLoadType type ATTRIBUTE_UNUSED ) {
 xmlParserCtxtPtr pctxt ;
 xmlParserInputPtr inputStream ;
 xmlDocPtr doc ;
 pctxt = xmlNewParserCtxt ( ) ;
 if ( pctxt == NULL ) return ( NULL ) ;
 if ( ( dict != NULL ) && ( pctxt -> dict != NULL ) ) {
 xmlDictFree ( pctxt -> dict ) ;
 pctxt -> dict = NULL ;
 }
 if ( dict != NULL ) {
 pctxt -> dict = dict ;
 xmlDictReference ( pctxt -> dict ) ;


 xmlCtxtUseOptions ( pctxt , options ) ;
 inputStream = xmlLoadExternalEntity ( ( const char * ) URI , NULL , pctxt ) ;
 if ( inputStream == NULL ) {
 xmlFreeParserCtxt ( pctxt ) ;
 return ( NULL ) ;
 }
 inputPush ( pctxt , inputStream ) ;
 if ( pctxt -> directory == NULL ) pctxt -> directory = xmlParserGetDirectory ( ( const char * ) URI ) ;
 xmlParseDocument ( pctxt ) ;
 if ( pctxt -> wellFormed ) {
 doc = pctxt -> myDoc ;
 }
 else {
 doc = NULL ;
 xmlFreeDoc ( pctxt -> myDoc ) ;
 pctxt -> myDoc = NULL ;
 }
 xmlFreeParserCtxt ( pctxt ) ;
 return ( doc ) ;
 }