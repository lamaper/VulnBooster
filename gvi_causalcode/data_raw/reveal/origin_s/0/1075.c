void vp8cx_mb_init_quantizer ( VP8_COMP * cpi , MACROBLOCK * x , int ok_to_skip ) {
 int i ;
 int QIndex ;
 MACROBLOCKD * xd = & x -> e_mbd ;
 int zbin_extra ;
 if ( xd -> segmentation_enabled ) {
 if ( xd -> mb_segement_abs_delta == SEGMENT_ABSDATA ) QIndex = xd -> segment_feature_data [ MB_LVL_ALT_Q ] [ xd -> mode_info_context -> mbmi . segment_id ] ;
 else {
 QIndex = cpi -> common . base_qindex + xd -> segment_feature_data [ MB_LVL_ALT_Q ] [ xd -> mode_info_context -> mbmi . segment_id ] ;
 QIndex = ( QIndex >= 0 ) ? ( ( QIndex <= MAXQ ) ? QIndex : MAXQ ) : 0 ;
 }
 }
 else QIndex = cpi -> common . base_qindex ;
 if ( ! ok_to_skip || QIndex != x -> q_index ) {
 xd -> dequant_y1_dc [ 0 ] = 1 ;
 xd -> dequant_y1 [ 0 ] = cpi -> common . Y1dequant [ QIndex ] [ 0 ] ;
 xd -> dequant_y2 [ 0 ] = cpi -> common . Y2dequant [ QIndex ] [ 0 ] ;
 xd -> dequant_uv [ 0 ] = cpi -> common . UVdequant [ QIndex ] [ 0 ] ;
 for ( i = 1 ;
 i < 16 ;
 i ++ ) {
 xd -> dequant_y1_dc [ i ] = xd -> dequant_y1 [ i ] = cpi -> common . Y1dequant [ QIndex ] [ 1 ] ;
 xd -> dequant_y2 [ i ] = cpi -> common . Y2dequant [ QIndex ] [ 1 ] ;
 xd -> dequant_uv [ i ] = cpi -> common . UVdequant [ QIndex ] [ 1 ] ;
 }

 i < 16 ;
 i ++ ) x -> e_mbd . block [ i ] . dequant = xd -> dequant_y1 ;
 for ( i = 16 ;
 i < 24 ;
 i ++ ) x -> e_mbd . block [ i ] . dequant = xd -> dequant_uv ;
 x -> e_mbd . block [ 24 ] . dequant = xd -> dequant_y2 ;

 for ( i = 0 ;
 i < 16 ;
 i ++ ) {
 x -> block [ i ] . quant = cpi -> Y1quant [ QIndex ] ;
 x -> block [ i ] . quant_fast = cpi -> Y1quant_fast [ QIndex ] ;
 x -> block [ i ] . quant_shift = cpi -> Y1quant_shift [ QIndex ] ;
 x -> block [ i ] . zbin = cpi -> Y1zbin [ QIndex ] ;
 x -> block [ i ] . round = cpi -> Y1round [ QIndex ] ;
 x -> block [ i ] . zrun_zbin_boost = cpi -> zrun_zbin_boost_y1 [ QIndex ] ;
 x -> block [ i ] . zbin_extra = ( short ) zbin_extra ;
 }
 zbin_extra = ZBIN_EXTRA_UV ;
 for ( i = 16 ;
 i < 24 ;
 i ++ ) {
 x -> block [ i ] . quant = cpi -> UVquant [ QIndex ] ;
 x -> block [ i ] . quant_fast = cpi -> UVquant_fast [ QIndex ] ;
 x -> block [ i ] . quant_shift = cpi -> UVquant_shift [ QIndex ] ;
 x -> block [ i ] . zbin = cpi -> UVzbin [ QIndex ] ;
 x -> block [ i ] . round = cpi -> UVround [ QIndex ] ;
 x -> block [ i ] . zrun_zbin_boost = cpi -> zrun_zbin_boost_uv [ QIndex ] ;
 x -> block [ i ] . zbin_extra = ( short ) zbin_extra ;
 }
 zbin_extra = ZBIN_EXTRA_Y2 ;
 x -> block [ 24 ] . quant_fast = cpi -> Y2quant_fast [ QIndex ] ;
 x -> block [ 24 ] . quant = cpi -> Y2quant [ QIndex ] ;
 x -> block [ 24 ] . quant_shift = cpi -> Y2quant_shift [ QIndex ] ;
 x -> block [ 24 ] . zbin = cpi -> Y2zbin [ QIndex ] ;
 x -> block [ 24 ] . round = cpi -> Y2round [ QIndex ] ;
 x -> block [ 24 ] . zrun_zbin_boost = cpi -> zrun_zbin_boost_y2 [ QIndex ] ;
 x -> block [ 24 ] . zbin_extra = ( short ) zbin_extra ;
 x -> q_index = QIndex ;
 x -> last_zbin_over_quant = x -> zbin_over_quant ;
 x -> last_zbin_mode_boost = x -> zbin_mode_boost ;
 x -> last_act_zbin_adj = x -> act_zbin_adj ;
 }
 else if ( x -> last_zbin_over_quant != x -> zbin_over_quant || x -> last_zbin_mode_boost != x -> zbin_mode_boost || x -> last_act_zbin_adj != x -> act_zbin_adj ) {
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
 x -> last_zbin_over_quant = x -> zbin_over_quant ;
 x -> last_zbin_mode_boost = x -> zbin_mode_boost ;
 x -> last_act_zbin_adj = x -> act_zbin_adj ;
 }
 }