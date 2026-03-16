static UHashtable * _uhash_init ( UHashtable * result , UHashFunction * keyHash , UKeyComparator * keyComp , UValueComparator * valueComp , int32_t primeIndex , UErrorCode * status ) {
 if ( U_FAILURE ( * status ) ) return NULL ;
 U_ASSERT ( keyHash != NULL ) ;
 U_ASSERT ( keyComp != NULL ) ;
 result -> keyHasher = keyHash ;
 result -> keyComparator = keyComp ;
 result -> valueComparator = valueComp ;
 result -> keyDeleter = NULL ;
 result -> valueDeleter = NULL ;
 result -> allocated = FALSE ;
 _uhash_internalSetResizePolicy ( result , U_GROW ) ;
 _uhash_allocate ( result , primeIndex , status ) ;
 if ( U_FAILURE ( * status ) ) {
 return NULL ;
 }
 return result ;
 }