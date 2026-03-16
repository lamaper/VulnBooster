static inline void expand_category ( COOKContext * q , int * category , int * category_index ) {
 int i ;
 for ( i = 0 ;
 i < q -> num_vectors ;
 i ++ ) {
 int idx = category_index [ i ] ;
 if ( ++ category [ idx ] >= FF_ARRAY_ELEMS ( dither_tab ) ) -- category [ idx ] ;
 }
 }