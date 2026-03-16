void vp9_temporal_filter_init ( ) {
 int i ;
 fixed_divide [ 0 ] = 0 ;
 for ( i = 1 ;
 i < 512 ;
 ++ i ) fixed_divide [ i ] = 0x80000 / i ;
 }