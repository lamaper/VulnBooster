static void transpose_perm ( int16_t * out , int16_t * in , int num_vect , const uint8_t line_len [ 2 ] , int length_div ) {
 int i , j ;
 int cont = 0 ;
 for ( i = 0 ;
 i < num_vect ;
 i ++ ) for ( j = 0 ;
 j < line_len [ i >= length_div ] ;
 j ++ ) out [ cont ++ ] = in [ j * num_vect + i ] ;
 }