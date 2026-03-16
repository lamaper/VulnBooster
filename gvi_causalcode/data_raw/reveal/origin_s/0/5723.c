static void setup_quantization ( VP9_COMMON * const cm , MACROBLOCKD * const xd , struct vp9_read_bit_buffer * rb ) {
 int update = 0 ;
 cm -> base_qindex = vp9_rb_read_literal ( rb , QINDEX_BITS ) ;
 update |= read_delta_q ( rb , & cm -> y_dc_delta_q ) ;
 update |= read_delta_q ( rb , & cm -> uv_dc_delta_q ) ;
 update |= read_delta_q ( rb , & cm -> uv_ac_delta_q ) ;
 if ( update ) vp9_init_dequantizer ( cm ) ;
 xd -> lossless = cm -> base_qindex == 0 && cm -> y_dc_delta_q == 0 && cm -> uv_dc_delta_q == 0 && cm -> uv_ac_delta_q == 0 ;
 }