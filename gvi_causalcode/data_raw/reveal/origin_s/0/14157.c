static int32_t pointerTOCPrefixBinarySearch ( const char * s , const PointerTOCEntry * toc , int32_t count ) {
 int32_t start = 0 ;
 int32_t limit = count ;
 int32_t startPrefixLength = 0 ;
 int32_t limitPrefixLength = 0 ;
 if ( count == 0 ) {
 return - 1 ;
 }
 if ( 0 == strcmpAfterPrefix ( s , toc [ 0 ] . entryName , & startPrefixLength ) ) {
 return 0 ;
 }
 ++ start ;
 -- limit ;
 if ( 0 == strcmpAfterPrefix ( s , toc [ limit ] . entryName , & limitPrefixLength ) ) {
 return limit ;
 }
 while ( start < limit ) {
 int32_t i = ( start + limit ) / 2 ;
 int32_t prefixLength = MIN ( startPrefixLength , limitPrefixLength ) ;
 int32_t cmp = strcmpAfterPrefix ( s , toc [ i ] . entryName , & prefixLength ) ;
 if ( cmp < 0 ) {
 limit = i ;
 limitPrefixLength = prefixLength ;
 }
 else if ( cmp == 0 ) {
 return i ;
 }
 else {
 start = i + 1 ;
 startPrefixLength = prefixLength ;
 }
 }
 return - 1 ;
 }