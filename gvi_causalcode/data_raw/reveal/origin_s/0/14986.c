static void init_bit_tree ( vp9_tree_index * p , int n ) {
 int i = 0 ;
 while ( ++ i < n ) {
 p [ 0 ] = p [ 1 ] = i << 1 ;
 p += 2 ;
 }
 p [ 0 ] = p [ 1 ] = 0 ;
 }