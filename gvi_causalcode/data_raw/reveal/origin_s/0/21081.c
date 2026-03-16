static void _uhash_rehash ( UHashtable * hash , UErrorCode * status ) {
 UHashElement * old = hash -> elements ;
 int32_t oldLength = hash -> length ;
 int32_t newPrimeIndex = hash -> primeIndex ;
 int32_t i ;
 if ( hash -> count > hash -> highWaterMark ) {
 if ( ++ newPrimeIndex >= PRIMES_LENGTH ) {
 return ;
 }
 }
 else if ( hash -> count < hash -> lowWaterMark ) {
 if ( -- newPrimeIndex < 0 ) {
 return ;
 }
 }
 else {
 return ;
 }
 _uhash_allocate ( hash , newPrimeIndex , status ) ;
 if ( U_FAILURE ( * status ) ) {
 hash -> elements = old ;
 hash -> length = oldLength ;
 return ;
 }
 for ( i = oldLength - 1 ;
 i >= 0 ;
 -- i ) {
 if ( ! IS_EMPTY_OR_DELETED ( old [ i ] . hashcode ) ) {
 UHashElement * e = _uhash_find ( hash , old [ i ] . key , old [ i ] . hashcode ) ;
 U_ASSERT ( e != NULL ) ;
 U_ASSERT ( e -> hashcode == HASH_EMPTY ) ;
 e -> key = old [ i ] . key ;
 e -> value = old [ i ] . value ;
 e -> hashcode = old [ i ] . hashcode ;
 ++ hash -> count ;
 }
 }
 uprv_free ( old ) ;
 }