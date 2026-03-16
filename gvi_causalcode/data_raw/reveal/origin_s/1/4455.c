static const DataHeader * offsetTOCLookupFn ( const UDataMemory * pData , const char * tocEntryName , int32_t * pLength , UErrorCode * pErrorCode ) {
 const UDataOffsetTOC * toc = ( UDataOffsetTOC * ) pData -> toc ;
 if ( toc != NULL ) {
 const char * base = ( const char * ) toc ;
 int32_t number , count = ( int32_t ) toc -> count ;

 number < count ;
 ++ number ) {
 fprintf ( stderr , "\tx%d: %s\n" , number , & base [ toc -> entry [ number ] . nameOffset ] ) ;
 }

 if ( number >= 0 ) {
 const UDataOffsetTOCEntry * entry = toc -> entry + number ;


 * pLength = ( int32_t ) ( entry [ 1 ] . dataOffset - entry -> dataOffset ) ;
 }
 else {
 * pLength = - 1 ;
 }
 return ( const DataHeader * ) ( base + entry -> dataOffset ) ;
 }
 else {


 }
 }
 else {


 }
 }