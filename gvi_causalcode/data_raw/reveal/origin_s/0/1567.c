static UHashElement * _uhash_find ( const UHashtable * hash , UHashTok key , int32_t hashcode ) {
 int32_t firstDeleted = - 1 ;
 int32_t theIndex , startIndex ;
 int32_t jump = 0 ;
 int32_t tableHash ;
 UHashElement * elements = hash -> elements ;
 hashcode &= 0x7FFFFFFF ;
 startIndex = theIndex = ( hashcode ^ 0x4000000 ) % hash -> length ;
 do {
 tableHash = elements [ theIndex ] . hashcode ;
 if ( tableHash == hashcode ) {
 if ( ( * hash -> keyComparator ) ( key , elements [ theIndex ] . key ) ) {
 return & ( elements [ theIndex ] ) ;
 }
 }
 else if ( ! IS_EMPTY_OR_DELETED ( tableHash ) ) {
 }
 else if ( tableHash == HASH_EMPTY ) {
 break ;
 }
 else if ( firstDeleted < 0 ) {
 firstDeleted = theIndex ;
 }
 if ( jump == 0 ) {
 jump = ( hashcode % ( hash -> length - 1 ) ) + 1 ;
 }
 theIndex = ( theIndex + jump ) % hash -> length ;
 }
 while ( theIndex != startIndex ) ;
 if ( firstDeleted >= 0 ) {
 theIndex = firstDeleted ;
 }
 else if ( tableHash != HASH_EMPTY ) {
 U_ASSERT ( FALSE ) ;
 return NULL ;
 }
 return & ( elements [ theIndex ] ) ;
 }