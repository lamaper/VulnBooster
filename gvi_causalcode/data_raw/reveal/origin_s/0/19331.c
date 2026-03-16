void vp8_update_zbin_extra ( VP8_COMP * cpi , MACROBLOCK * x ) {
 int i ;
 int QIndex = x -> q_index ;
 int zbin_extra ;
 zbin_extra = ZBIN_EXTRA_Y ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) x -> block [ i ] . zbin_extra = ( short ) zbin_extra ;
 zbin_extra = ZBIN_EXTRA_UV ;
 for ( i = 16 ;
 i < 24 ;
 i ++ ) x -> block [ i ] . zbin_extra = ( short ) zbin_extra ;
 zbin_extra = ZBIN_EXTRA_Y2 ;
 x -> block [ 24 ] . zbin_extra = ( short ) zbin_extra ;
 }