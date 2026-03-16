void vp8_set_quantizer ( struct VP8_COMP * cpi , int Q ) {
 VP8_COMMON * cm = & cpi -> common ;
 MACROBLOCKD * mbd = & cpi -> mb . e_mbd ;
 int update = 0 ;
 int new_delta_q ;
 cm -> base_qindex = Q ;
 cm -> y1dc_delta_q = 0 ;
 cm -> y2ac_delta_q = 0 ;
 cm -> uvdc_delta_q = 0 ;
 cm -> uvac_delta_q = 0 ;
 if ( Q < 4 ) {
 new_delta_q = 4 - Q ;
 }
 else new_delta_q = 0 ;
 update |= cm -> y2dc_delta_q != new_delta_q ;
 cm -> y2dc_delta_q = new_delta_q ;
 mbd -> segment_feature_data [ MB_LVL_ALT_Q ] [ 0 ] = cpi -> segment_feature_data [ MB_LVL_ALT_Q ] [ 0 ] ;
 mbd -> segment_feature_data [ MB_LVL_ALT_Q ] [ 1 ] = cpi -> segment_feature_data [ MB_LVL_ALT_Q ] [ 1 ] ;
 mbd -> segment_feature_data [ MB_LVL_ALT_Q ] [ 2 ] = cpi -> segment_feature_data [ MB_LVL_ALT_Q ] [ 2 ] ;
 mbd -> segment_feature_data [ MB_LVL_ALT_Q ] [ 3 ] = cpi -> segment_feature_data [ MB_LVL_ALT_Q ] [ 3 ] ;
 if ( update ) vp8cx_init_quantizer ( cpi ) ;
 }