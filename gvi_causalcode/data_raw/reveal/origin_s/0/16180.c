static UHashTok _uhash_internalRemoveElement ( UHashtable * hash , UHashElement * e ) {
 UHashTok empty ;
 U_ASSERT ( ! IS_EMPTY_OR_DELETED ( e -> hashcode ) ) ;
 -- hash -> count ;
 empty . pointer = NULL ;
 empty . integer = 0 ;
 return _uhash_setElement ( hash , e , HASH_DELETED , empty , empty , 0 ) ;
 }