static UHashTok _uhash_remove ( UHashtable * hash , UHashTok key ) {
 UHashTok result ;
 UHashElement * e = _uhash_find ( hash , key , hash -> keyHasher ( key ) ) ;
 U_ASSERT ( e != NULL ) ;
 result . pointer = NULL ;
 result . integer = 0 ;
 if ( ! IS_EMPTY_OR_DELETED ( e -> hashcode ) ) {
 result = _uhash_internalRemoveElement ( hash , e ) ;
 if ( hash -> count < hash -> lowWaterMark ) {
 UErrorCode status = U_ZERO_ERROR ;
 _uhash_rehash ( hash , & status ) ;
 }
 }
 return result ;
 }