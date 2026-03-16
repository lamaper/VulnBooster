static void linear_perm ( int16_t * out , int16_t * in , int n_blocks , int size ) {
 int block_size = size_blocks ;
 int i ;
 for ( i = 0 ;
 i < size ;
 i ++ ) out [ i ] = block_size * ( in [ i ] % n_blocks ) + in [ i ] / n_blocks ;
 }