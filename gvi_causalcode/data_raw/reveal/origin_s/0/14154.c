static void encode_quantization ( const VP9_COMMON * const cm , struct vp9_write_bit_buffer * wb ) {
 vp9_wb_write_literal ( wb , cm -> base_qindex , QINDEX_BITS ) ;
 write_delta_q ( wb , cm -> y_dc_delta_q ) ;
 write_delta_q ( wb , cm -> uv_dc_delta_q ) ;
 write_delta_q ( wb , cm -> uv_ac_delta_q ) ;
 }