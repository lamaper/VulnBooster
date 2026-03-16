void debugCB_fromU ( const void * context , UConverterFromUnicodeArgs * fromUArgs , const UChar * codeUnits , int32_t length , UChar32 codePoint , UConverterCallbackReason reason , UErrorCode * err ) {
 debugCBContext * ctx = ( debugCBContext * ) context ;


 fprintf ( stderr , "debugCB_fromU: Context %p:%d magic is 0x%x should be 0xC0FFEE.\n" , ctx , ctx -> serial , ctx -> magic ) ;
 return ;
 }
 if ( reason == UCNV_CLONE ) {
 UConverterFromUCallback saveCallback ;
 const void * saveContext ;
 debugCBContext * cloned ;
 UErrorCode subErr = U_ZERO_ERROR ;


 if ( cloned == NULL ) {
 fprintf ( stderr , "debugCB_fromU: internal clone failed on %p\n" , ctx ) ;
 * err = U_MEMORY_ALLOCATION_ERROR ;
 return ;
 }
 ucnv_setFromUCallBack ( fromUArgs -> converter , cloned -> subCallback , cloned -> subContext , & saveCallback , & saveContext , & subErr ) ;
 if ( cloned -> subCallback != NULL ) {


 }
 else {
 printf ( "debugCB_fromU:%p, NOT calling subCB, it's NULL\n" , ctx ) ;
 }
 ucnv_setFromUCallBack ( fromUArgs -> converter , saveCallback , cloned , & cloned -> subCallback , & cloned -> subContext , & subErr ) ;
 if ( U_FAILURE ( subErr ) ) {
 * err = subErr ;
 }
 }
 if ( ctx -> subCallback != NULL && reason != UCNV_CLONE ) {
 ctx -> subCallback ( ctx -> subContext , fromUArgs , codeUnits , length , codePoint , reason , err ) ;
 }
 if ( reason == UCNV_CLOSE ) {


 }

