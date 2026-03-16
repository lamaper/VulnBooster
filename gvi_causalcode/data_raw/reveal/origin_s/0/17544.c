static void qcms_transform_module_gamma_table ( struct qcms_modular_transform * transform , float * src , float * dest , size_t length ) {
 size_t i ;
 float out_r , out_g , out_b ;
 for ( i = 0 ;
 i < length ;
 i ++ ) {
 float in_r = * src ++ ;
 float in_g = * src ++ ;
 float in_b = * src ++ ;
 out_r = lut_interp_linear_float ( in_r , transform -> input_clut_table_r , 256 ) ;
 out_g = lut_interp_linear_float ( in_g , transform -> input_clut_table_g , 256 ) ;
 out_b = lut_interp_linear_float ( in_b , transform -> input_clut_table_b , 256 ) ;
 * dest ++ = clamp_float ( out_r ) ;
 * dest ++ = clamp_float ( out_g ) ;
 * dest ++ = clamp_float ( out_b ) ;
 }
 }