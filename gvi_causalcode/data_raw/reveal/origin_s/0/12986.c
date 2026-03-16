int ff_rv34_get_start_offset ( GetBitContext * gb , int mb_size ) {
 int i ;
 for ( i = 0 ;
 i < 5 ;
 i ++ ) if ( rv34_mb_max_sizes [ i ] >= mb_size - 1 ) break ;
 return rv34_mb_bits_sizes [ i ] ;
 }