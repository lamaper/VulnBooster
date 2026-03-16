unsigned int vp9_get_mb_ss_c ( const int16_t * src_ptr ) {
 unsigned int i , sum = 0 ;
 for ( i = 0 ;
 i < 256 ;
 ++ i ) {
 sum += src_ptr [ i ] * src_ptr [ i ] ;
 }
 return sum ;
 }