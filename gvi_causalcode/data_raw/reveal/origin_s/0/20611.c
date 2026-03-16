static void _uhash_allocate ( UHashtable * hash , int32_t primeIndex , UErrorCode * status ) {
 UHashElement * p , * limit ;
 UHashTok emptytok ;
 if ( U_FAILURE ( * status ) ) return ;
 U_ASSERT ( primeIndex >= 0 && primeIndex < PRIMES_LENGTH ) ;
 hash -> primeIndex = primeIndex ;
 hash -> length = PRIMES [ primeIndex ] ;
 p = hash -> elements = ( UHashElement * ) uprv_malloc ( sizeof ( UHashElement ) * hash -> length ) ;
 if ( hash -> elements == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 return ;
 }
 emptytok . pointer = NULL ;
 emptytok . integer = 0 ;
 limit = p + hash -> length ;
 while ( p < limit ) {
 p -> key = emptytok ;
 p -> value = emptytok ;
 p -> hashcode = HASH_EMPTY ;
 ++ p ;
 }
 hash -> count = 0 ;
 hash -> lowWaterMark = ( int32_t ) ( hash -> length * hash -> lowWaterRatio ) ;
 hash -> highWaterMark = ( int32_t ) ( hash -> length * hash -> highWaterRatio ) ;
 }