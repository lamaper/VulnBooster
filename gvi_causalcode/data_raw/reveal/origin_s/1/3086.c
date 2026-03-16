void vp9_init_quantizer ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 QUANTS * const quants = & cpi -> quants ;
 int i , q , quant ;
 for ( q = 0 ;
 q < QINDEX_RANGE ;
 q ++ ) {
 const int qzbin_factor = q == 0 ? 64 : ( vp9_dc_quant ( q , 0 ) < 148 ? 84 : 80 ) ;
 const int qrounding_factor = q == 0 ? 64 : 48 ;
 for ( i = 0 ;
 i < 2 ;
 ++ i ) {
 int qrounding_factor_fp = i == 0 ? 48 : 42 ;
 if ( q == 0 ) qrounding_factor_fp = 64 ;
 quant = i == 0 ? vp9_dc_quant ( q , cm -> y_dc_delta_q ) : vp9_ac_quant ( q , 0 ) ;
 invert_quant ( & quants -> y_quant [ q ] [ i ] , & quants -> y_quant_shift [ q ] [ i ] , quant ) ;
 quants -> y_quant_fp [ q ] [ i ] = ( 1 << 16 ) / quant ;
 quants -> y_round_fp [ q ] [ i ] = ( qrounding_factor_fp * quant ) >> 7 ;
 quants -> y_zbin [ q ] [ i ] = ROUND_POWER_OF_TWO ( qzbin_factor * quant , 7 ) ;
 quants -> y_round [ q ] [ i ] = ( qrounding_factor * quant ) >> 7 ;
 cm -> y_dequant [ q ] [ i ] = quant ;
 quant = i == 0 ? vp9_dc_quant ( q , cm -> uv_dc_delta_q ) : vp9_ac_quant ( q , cm -> uv_ac_delta_q ) ;
 invert_quant ( & quants -> uv_quant [ q ] [ i ] , & quants -> uv_quant_shift [ q ] [ i ] , quant ) ;
 quants -> uv_quant_fp [ q ] [ i ] = ( 1 << 16 ) / quant ;
 quants -> uv_round_fp [ q ] [ i ] = ( qrounding_factor_fp * quant ) >> 7 ;
 quants -> uv_zbin [ q ] [ i ] = ROUND_POWER_OF_TWO ( qzbin_factor * quant , 7 ) ;
 quants -> uv_round [ q ] [ i ] = ( qrounding_factor * quant ) >> 7 ;
 cm -> uv_dequant [ q ] [ i ] = quant ;
 }
 for ( i = 2 ;
 i < 8 ;
 i ++ ) {
 quants -> y_quant [ q ] [ i ] = quants -> y_quant [ q ] [ 1 ] ;
 quants -> y_quant_fp [ q ] [ i ] = quants -> y_quant_fp [ q ] [ 1 ] ;
 quants -> y_round_fp [ q ] [ i ] = quants -> y_round_fp [ q ] [ 1 ] ;
 quants -> y_quant_shift [ q ] [ i ] = quants -> y_quant_shift [ q ] [ 1 ] ;
 quants -> y_zbin [ q ] [ i ] = quants -> y_zbin [ q ] [ 1 ] ;
 quants -> y_round [ q ] [ i ] = quants -> y_round [ q ] [ 1 ] ;
 cm -> y_dequant [ q ] [ i ] = cm -> y_dequant [ q ] [ 1 ] ;
 quants -> uv_quant [ q ] [ i ] = quants -> uv_quant [ q ] [ 1 ] ;
 quants -> uv_quant_fp [ q ] [ i ] = quants -> uv_quant_fp [ q ] [ 1 ] ;
 quants -> uv_round_fp [ q ] [ i ] = quants -> uv_round_fp [ q ] [ 1 ] ;
 quants -> uv_quant_shift [ q ] [ i ] = quants -> uv_quant_shift [ q ] [ 1 ] ;
 quants -> uv_zbin [ q ] [ i ] = quants -> uv_zbin [ q ] [ 1 ] ;
 quants -> uv_round [ q ] [ i ] = quants -> uv_round [ q ] [ 1 ] ;
 cm -> uv_dequant [ q ] [ i ] = cm -> uv_dequant [ q ] [ 1 ] ;
 }
 }
 }