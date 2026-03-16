static int count_hq_slice ( SliceArgs * slice , int quant_idx ) {
 int x , y ;
 uint8_t quants [ MAX_DWT_LEVELS ] [ 4 ] ;
 int bits = 0 , p , level , orientation ;
 VC2EncContext * s = slice -> ctx ;
 if ( slice -> cache [ quant_idx ] ) return slice -> cache [ quant_idx ] ;
 bits += 8 * s -> prefix_bytes ;
 bits += 8 ;
 for ( level = 0 ;
 level < s -> wavelet_depth ;
 level ++ ) for ( orientation = ! ! level ;
 orientation < 4 ;
 orientation ++ ) quants [ level ] [ orientation ] = FFMAX ( quant_idx - s -> quant [ level ] [ orientation ] , 0 ) ;
 for ( p = 0 ;
 p < 3 ;
 p ++ ) {
 int bytes_start , bytes_len , pad_s , pad_c ;
 bytes_start = bits >> 3 ;
 bits += 8 ;
 for ( level = 0 ;
 level < s -> wavelet_depth ;
 level ++ ) {
 for ( orientation = ! ! level ;
 orientation < 4 ;
 orientation ++ ) {
 SubBand * b = & s -> plane [ p ] . band [ level ] [ orientation ] ;
 const int q_idx = quants [ level ] [ orientation ] ;
 const uint8_t * len_lut = & s -> coef_lut_len [ q_idx * COEF_LUT_TAB ] ;
 const int qfactor = ff_dirac_qscale_tab [ q_idx ] ;
 const int left = b -> width * slice -> x / s -> num_x ;
 const int right = b -> width * ( slice -> x + 1 ) / s -> num_x ;
 const int top = b -> height * slice -> y / s -> num_y ;
 const int bottom = b -> height * ( slice -> y + 1 ) / s -> num_y ;
 dwtcoef * buf = b -> buf + top * b -> stride ;
 for ( y = top ;
 y < bottom ;
 y ++ ) {
 for ( x = left ;
 x < right ;
 x ++ ) {
 uint32_t c_abs = FFABS ( buf [ x ] ) ;
 if ( c_abs < COEF_LUT_TAB ) {
 bits += len_lut [ c_abs ] ;
 }
 else {
 c_abs = QUANT ( c_abs , qfactor ) ;
 bits += count_vc2_ue_uint ( c_abs ) ;
 bits += ! ! c_abs ;
 }
 }
 buf += b -> stride ;
 }
 }
 }
 bits += FFALIGN ( bits , 8 ) - bits ;
 bytes_len = ( bits >> 3 ) - bytes_start - 1 ;
 pad_s = FFALIGN ( bytes_len , s -> size_scaler ) / s -> size_scaler ;
 pad_c = ( pad_s * s -> size_scaler ) - bytes_len ;
 bits += pad_c * 8 ;
 }
 slice -> cache [ quant_idx ] = bits ;
 return bits ;
 }