static const DataHeader * U_CALLCONV pointerTOCLookupFn ( const UDataMemory * pData , const char * name , int32_t * pLength , UErrorCode * pErrorCode ) {
 ( void ) pErrorCode ;
 if ( pData -> toc != NULL ) {
 const PointerTOC * toc = ( PointerTOC * ) pData -> toc ;
 int32_t number , count = ( int32_t ) toc -> count ;

 number < count ;
 ++ number ) {
 fprintf ( stderr , "\tx%d: %s\n" , number , toc -> entry [ number ] . entryName ) ;
 }

 if ( number >= 0 ) {


 return UDataMemory_normalizeDataPointer ( toc -> entry [ number ] . pHeader ) ;
 }
 else {


 }
 }
 else {
 return pData -> pHeader ;
 }
 }