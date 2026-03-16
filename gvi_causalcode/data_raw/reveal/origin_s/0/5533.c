void vp8cx_init_quantizer ( VP8_COMP * cpi ) {
 int i ;
 int quant_val ;
 int Q ;
 int zbin_boost [ 16 ] = {
 0 , 0 , 8 , 10 , 12 , 14 , 16 , 20 , 24 , 28 , 32 , 36 , 40 , 44 , 44 , 44 }
 ;
 for ( Q = 0 ;
 Q < QINDEX_RANGE ;
 Q ++ ) {
 quant_val = vp8_dc_quant ( Q , cpi -> common . y1dc_delta_q ) ;
 cpi -> Y1quant_fast [ Q ] [ 0 ] = ( 1 << 16 ) / quant_val ;
 invert_quant ( cpi -> sf . improved_quant , cpi -> Y1quant [ Q ] + 0 , cpi -> Y1quant_shift [ Q ] + 0 , quant_val ) ;
 cpi -> Y1zbin [ Q ] [ 0 ] = ( ( qzbin_factors [ Q ] * quant_val ) + 64 ) >> 7 ;
 cpi -> Y1round [ Q ] [ 0 ] = ( qrounding_factors [ Q ] * quant_val ) >> 7 ;
 cpi -> common . Y1dequant [ Q ] [ 0 ] = quant_val ;
 cpi -> zrun_zbin_boost_y1 [ Q ] [ 0 ] = ( quant_val * zbin_boost [ 0 ] ) >> 7 ;
 quant_val = vp8_dc2quant ( Q , cpi -> common . y2dc_delta_q ) ;
 cpi -> Y2quant_fast [ Q ] [ 0 ] = ( 1 << 16 ) / quant_val ;
 invert_quant ( cpi -> sf . improved_quant , cpi -> Y2quant [ Q ] + 0 , cpi -> Y2quant_shift [ Q ] + 0 , quant_val ) ;
 cpi -> Y2zbin [ Q ] [ 0 ] = ( ( qzbin_factors_y2 [ Q ] * quant_val ) + 64 ) >> 7 ;
 cpi -> Y2round [ Q ] [ 0 ] = ( qrounding_factors_y2 [ Q ] * quant_val ) >> 7 ;
 cpi -> common . Y2dequant [ Q ] [ 0 ] = quant_val ;
 cpi -> zrun_zbin_boost_y2 [ Q ] [ 0 ] = ( quant_val * zbin_boost [ 0 ] ) >> 7 ;
 quant_val = vp8_dc_uv_quant ( Q , cpi -> common . uvdc_delta_q ) ;
 cpi -> UVquant_fast [ Q ] [ 0 ] = ( 1 << 16 ) / quant_val ;
 invert_quant ( cpi -> sf . improved_quant , cpi -> UVquant [ Q ] + 0 , cpi -> UVquant_shift [ Q ] + 0 , quant_val ) ;
 cpi -> UVzbin [ Q ] [ 0 ] = ( ( qzbin_factors [ Q ] * quant_val ) + 64 ) >> 7 ;
 ;
 cpi -> UVround [ Q ] [ 0 ] = ( qrounding_factors [ Q ] * quant_val ) >> 7 ;
 cpi -> common . UVdequant [ Q ] [ 0 ] = quant_val ;
 cpi -> zrun_zbin_boost_uv [ Q ] [ 0 ] = ( quant_val * zbin_boost [ 0 ] ) >> 7 ;
 quant_val = vp8_ac_yquant ( Q ) ;
 cpi -> Y1quant_fast [ Q ] [ 1 ] = ( 1 << 16 ) / quant_val ;
 invert_quant ( cpi -> sf . improved_quant , cpi -> Y1quant [ Q ] + 1 , cpi -> Y1quant_shift [ Q ] + 1 , quant_val ) ;
 cpi -> Y1zbin [ Q ] [ 1 ] = ( ( qzbin_factors [ Q ] * quant_val ) + 64 ) >> 7 ;
 cpi -> Y1round [ Q ] [ 1 ] = ( qrounding_factors [ Q ] * quant_val ) >> 7 ;
 cpi -> common . Y1dequant [ Q ] [ 1 ] = quant_val ;
 cpi -> zrun_zbin_boost_y1 [ Q ] [ 1 ] = ( quant_val * zbin_boost [ 1 ] ) >> 7 ;
 quant_val = vp8_ac2quant ( Q , cpi -> common . y2ac_delta_q ) ;
 cpi -> Y2quant_fast [ Q ] [ 1 ] = ( 1 << 16 ) / quant_val ;
 invert_quant ( cpi -> sf . improved_quant , cpi -> Y2quant [ Q ] + 1 , cpi -> Y2quant_shift [ Q ] + 1 , quant_val ) ;
 cpi -> Y2zbin [ Q ] [ 1 ] = ( ( qzbin_factors_y2 [ Q ] * quant_val ) + 64 ) >> 7 ;
 cpi -> Y2round [ Q ] [ 1 ] = ( qrounding_factors_y2 [ Q ] * quant_val ) >> 7 ;
 cpi -> common . Y2dequant [ Q ] [ 1 ] = quant_val ;
 cpi -> zrun_zbin_boost_y2 [ Q ] [ 1 ] = ( quant_val * zbin_boost [ 1 ] ) >> 7 ;
 quant_val = vp8_ac_uv_quant ( Q , cpi -> common . uvac_delta_q ) ;
 cpi -> UVquant_fast [ Q ] [ 1 ] = ( 1 << 16 ) / quant_val ;
 invert_quant ( cpi -> sf . improved_quant , cpi -> UVquant [ Q ] + 1 , cpi -> UVquant_shift [ Q ] + 1 , quant_val ) ;
 cpi -> UVzbin [ Q ] [ 1 ] = ( ( qzbin_factors [ Q ] * quant_val ) + 64 ) >> 7 ;
 cpi -> UVround [ Q ] [ 1 ] = ( qrounding_factors [ Q ] * quant_val ) >> 7 ;
 cpi -> common . UVdequant [ Q ] [ 1 ] = quant_val ;
 cpi -> zrun_zbin_boost_uv [ Q ] [ 1 ] = ( quant_val * zbin_boost [ 1 ] ) >> 7 ;
 for ( i = 2 ;
 i < 16 ;
 i ++ ) {
 cpi -> Y1quant_fast [ Q ] [ i ] = cpi -> Y1quant_fast [ Q ] [ 1 ] ;
 cpi -> Y1quant [ Q ] [ i ] = cpi -> Y1quant [ Q ] [ 1 ] ;
 cpi -> Y1quant_shift [ Q ] [ i ] = cpi -> Y1quant_shift [ Q ] [ 1 ] ;
 cpi -> Y1zbin [ Q ] [ i ] = cpi -> Y1zbin [ Q ] [ 1 ] ;
 cpi -> Y1round [ Q ] [ i ] = cpi -> Y1round [ Q ] [ 1 ] ;
 cpi -> zrun_zbin_boost_y1 [ Q ] [ i ] = ( cpi -> common . Y1dequant [ Q ] [ 1 ] * zbin_boost [ i ] ) >> 7 ;
 cpi -> Y2quant_fast [ Q ] [ i ] = cpi -> Y2quant_fast [ Q ] [ 1 ] ;
 cpi -> Y2quant [ Q ] [ i ] = cpi -> Y2quant [ Q ] [ 1 ] ;
 cpi -> Y2quant_shift [ Q ] [ i ] = cpi -> Y2quant_shift [ Q ] [ 1 ] ;
 cpi -> Y2zbin [ Q ] [ i ] = cpi -> Y2zbin [ Q ] [ 1 ] ;
 cpi -> Y2round [ Q ] [ i ] = cpi -> Y2round [ Q ] [ 1 ] ;
 cpi -> zrun_zbin_boost_y2 [ Q ] [ i ] = ( cpi -> common . Y2dequant [ Q ] [ 1 ] * zbin_boost [ i ] ) >> 7 ;
 cpi -> UVquant_fast [ Q ] [ i ] = cpi -> UVquant_fast [ Q ] [ 1 ] ;
 cpi -> UVquant [ Q ] [ i ] = cpi -> UVquant [ Q ] [ 1 ] ;
 cpi -> UVquant_shift [ Q ] [ i ] = cpi -> UVquant_shift [ Q ] [ 1 ] ;
 cpi -> UVzbin [ Q ] [ i ] = cpi -> UVzbin [ Q ] [ 1 ] ;
 cpi -> UVround [ Q ] [ i ] = cpi -> UVround [ Q ] [ 1 ] ;
 cpi -> zrun_zbin_boost_uv [ Q ] [ i ] = ( cpi -> common . UVdequant [ Q ] [ 1 ] * zbin_boost [ i ] ) >> 7 ;
 }
 }
 }