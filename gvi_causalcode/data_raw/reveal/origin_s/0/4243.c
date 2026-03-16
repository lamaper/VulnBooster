static void qcms_transform_module_gamma_lut ( struct qcms_modular_transform * transform , float * src , float * dest , size_t length ) {
 size_t i ;
 float out_r , out_g , out_b ;
 for ( i = 0 ;
 i < length ;
 i ++ ) {
 float in_r = * src ++ ;
 float in_g = * src ++ ;
 float in_b = * src ++ ;
 out_r = lut_interp_linear ( in_r , transform -> output_gamma_lut_r , transform -> output_gamma_lut_r_length ) ;
 out_g = lut_interp_linear ( in_g , transform -> output_gamma_lut_g , transform -> output_gamma_lut_g_length ) ;
 out_b = lut_interp_linear ( in_b , transform -> output_gamma_lut_b , transform -> output_gamma_lut_b_length ) ;
 * dest ++ = clamp_float ( out_r ) ;
 * dest ++ = clamp_float ( out_g ) ;
 * dest ++ = clamp_float ( out_b ) ;
 }
 }