void vp9_update_zbin_extra ( VP9_COMP * cpi , MACROBLOCK * x ) {
 const int qindex = x -> q_index ;
 const int y_zbin_extra = ( cpi -> common . y_dequant [ qindex ] [ 1 ] * cpi -> zbin_mode_boost ) >> 7 ;
 const int uv_zbin_extra = ( cpi -> common . uv_dequant [ qindex ] [ 1 ] * cpi -> zbin_mode_boost ) >> 7 ;
 x -> plane [ 0 ] . zbin_extra = ( int16_t ) y_zbin_extra ;
 x -> plane [ 1 ] . zbin_extra = ( int16_t ) uv_zbin_extra ;
 x -> plane [ 2 ] . zbin_extra = ( int16_t ) uv_zbin_extra ;
 }