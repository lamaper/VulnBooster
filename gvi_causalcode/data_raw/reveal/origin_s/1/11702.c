void vp9_lpf_horizontal_16_sse2 ( unsigned char * s , int p , const unsigned char * _blimit , const unsigned char * _limit , const unsigned char * _thresh , int count ) {
 if ( count == 1 ) mb_lpf_horizontal_edge_w_sse2_8 ( s , p , _blimit , _limit , _thresh ) ;
 else mb_lpf_horizontal_edge_w_sse2_16 ( s , p , _blimit , _limit , _thresh ) ;
 }