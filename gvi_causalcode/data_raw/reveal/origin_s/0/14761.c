void vp9_init_dequantizer ( VP9_COMMON * cm ) {
 int q ;
 for ( q = 0 ;
 q < QINDEX_RANGE ;
 q ++ ) {
 cm -> y_dequant [ q ] [ 0 ] = vp9_dc_quant ( q , cm -> y_dc_delta_q ) ;
 cm -> y_dequant [ q ] [ 1 ] = vp9_ac_quant ( q , 0 ) ;
 cm -> uv_dequant [ q ] [ 0 ] = vp9_dc_quant ( q , cm -> uv_dc_delta_q ) ;
 cm -> uv_dequant [ q ] [ 1 ] = vp9_ac_quant ( q , cm -> uv_ac_delta_q ) ;
 }
 }