static void get_bits_align32 ( GetBitContext * s ) {
 int n = ( - get_bits_count ( s ) ) & 31 ;
 if ( n ) skip_bits ( s , n ) ;
 }