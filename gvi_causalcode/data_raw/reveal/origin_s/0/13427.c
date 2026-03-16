static UHashTok _uhash_put ( UHashtable * hash , UHashTok key , UHashTok value , int8_t hint , UErrorCode * status ) {
 int32_t hashcode ;
 UHashElement * e ;
 UHashTok emptytok ;
 if ( U_FAILURE ( * status ) ) {
 goto err ;
 }
 U_ASSERT ( hash != NULL ) ;
 if ( ( hint & HINT_VALUE_POINTER ) && value . pointer == NULL ) {
 return _uhash_remove ( hash , key ) ;
 }
 if ( hash -> count > hash -> highWaterMark ) {
 _uhash_rehash ( hash , status ) ;
 if ( U_FAILURE ( * status ) ) {
 goto err ;
 }
 }
 hashcode = ( * hash -> keyHasher ) ( key ) ;
 e = _uhash_find ( hash , key , hashcode ) ;
 U_ASSERT ( e != NULL ) ;
 if ( IS_EMPTY_OR_DELETED ( e -> hashcode ) ) {
 ++ hash -> count ;
 if ( hash -> count == hash -> length ) {
 -- hash -> count ;
 * status = U_MEMORY_ALLOCATION_ERROR ;
 goto err ;
 }
 }
 return _uhash_setElement ( hash , e , hashcode & 0x7FFFFFFF , key , value , hint ) ;
 err : HASH_DELETE_KEY_VALUE ( hash , key . pointer , value . pointer ) ;
 emptytok . pointer = NULL ;
 emptytok . integer = 0 ;
 return emptytok ;
 }