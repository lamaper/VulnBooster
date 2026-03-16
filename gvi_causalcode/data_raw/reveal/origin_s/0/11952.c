debugCBContext * debugCB_openContext ( ) {
 debugCBContext * ctx ;
 ctx = malloc ( sizeof ( debugCBContext ) ) ;
 if ( ctx != NULL ) {
 ctx -> magic = 0xC0FFEE ;
 ctx -> serial = debugCB_nextSerial ( ) ;
 ctx -> subCallback = NULL ;
 ctx -> subContext = NULL ;


 return ctx ;
 }