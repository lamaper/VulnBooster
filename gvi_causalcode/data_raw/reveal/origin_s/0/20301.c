static UHashtable * _uhash_create ( UHashFunction * keyHash , UKeyComparator * keyComp , UValueComparator * valueComp , int32_t primeIndex , UErrorCode * status ) {
 UHashtable * result ;
 if ( U_FAILURE ( * status ) ) return NULL ;
 result = ( UHashtable * ) uprv_malloc ( sizeof ( UHashtable ) ) ;
 if ( result == NULL ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 return NULL ;
 }
 _uhash_init ( result , keyHash , keyComp , valueComp , primeIndex , status ) ;
 result -> allocated = TRUE ;
 if ( U_FAILURE ( * status ) ) {
 uprv_free ( result ) ;
 return NULL ;
 }
 return result ;
 }