static debugCBContext * debugCB_clone ( debugCBContext * ctx ) {
 debugCBContext * newCtx ;
 newCtx = malloc ( sizeof ( debugCBContext ) ) ;
 newCtx -> serial = debugCB_nextSerial ( ) ;
 newCtx -> magic = 0xC0FFEE ;
 newCtx -> subCallback = ctx -> subCallback ;
 newCtx -> subContext = ctx -> subContext ;


 }