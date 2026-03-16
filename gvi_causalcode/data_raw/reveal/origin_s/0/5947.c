void vp9_set_quantizer ( VP9_COMMON * cm , int q ) {
 cm -> base_qindex = q ;
 cm -> y_dc_delta_q = 0 ;
 cm -> uv_dc_delta_q = 0 ;
 cm -> uv_ac_delta_q = 0 ;
 }