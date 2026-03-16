int find_set ( REP_SETS * sets , REP_SET * find ) {
 uint i ;
 for ( i = 0 ;
 i < sets -> count - 1 ;
 i ++ ) {
 if ( ! cmp_bits ( sets -> set + i , find ) ) {
 free_last_set ( sets ) ;
 return i ;
 }
 }
 return i ;
 }