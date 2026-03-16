static void encode_subband ( VC2EncContext * s , PutBitContext * pb , int sx , int sy , SubBand * b , int quant ) {
 int x , y ;
 const int left = b -> width * ( sx + 0 ) / s -> num_x ;
 const int right = b -> width * ( sx + 1 ) / s -> num_x ;
 const int top = b -> height * ( sy + 0 ) / s -> num_y ;
 const int bottom = b -> height * ( sy + 1 ) / s -> num_y ;
 const int qfactor = ff_dirac_qscale_tab [ quant ] ;
 const uint8_t * len_lut = & s -> coef_lut_len [ quant * COEF_LUT_TAB ] ;
 const uint32_t * val_lut = & s -> coef_lut_val [ quant * COEF_LUT_TAB ] ;
 dwtcoef * coeff = b -> buf + top * b -> stride ;
 for ( y = top ;
 y < bottom ;
 y ++ ) {
 for ( x = left ;
 x < right ;
 x ++ ) {
 const int neg = coeff [ x ] < 0 ;
 uint32_t c_abs = FFABS ( coeff [ x ] ) ;
 if ( c_abs < COEF_LUT_TAB ) {
 put_bits ( pb , len_lut [ c_abs ] , val_lut [ c_abs ] | neg ) ;
 }
 else {
 c_abs = QUANT ( c_abs , qfactor ) ;
 put_vc2_ue_uint ( pb , c_abs ) ;
 if ( c_abs ) put_bits ( pb , 1 , neg ) ;
 }
 }
 coeff += b -> stride ;
 }
 }