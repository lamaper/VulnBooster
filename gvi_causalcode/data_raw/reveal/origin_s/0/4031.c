static void qcms_transform_module_matrix_translate ( struct qcms_modular_transform * transform , float * src , float * dest , size_t length ) {
 size_t i ;
 struct matrix mat ;
 mat . m [ 0 ] [ 0 ] = transform -> matrix . m [ 0 ] [ 0 ] ;
 mat . m [ 1 ] [ 0 ] = transform -> matrix . m [ 0 ] [ 1 ] ;
 mat . m [ 2 ] [ 0 ] = transform -> matrix . m [ 0 ] [ 2 ] ;
 mat . m [ 0 ] [ 1 ] = transform -> matrix . m [ 1 ] [ 0 ] ;
 mat . m [ 1 ] [ 1 ] = transform -> matrix . m [ 1 ] [ 1 ] ;
 mat . m [ 2 ] [ 1 ] = transform -> matrix . m [ 1 ] [ 2 ] ;
 mat . m [ 0 ] [ 2 ] = transform -> matrix . m [ 2 ] [ 0 ] ;
 mat . m [ 1 ] [ 2 ] = transform -> matrix . m [ 2 ] [ 1 ] ;
 mat . m [ 2 ] [ 2 ] = transform -> matrix . m [ 2 ] [ 2 ] ;
 for ( i = 0 ;
 i < length ;
 i ++ ) {
 float in_r = * src ++ ;
 float in_g = * src ++ ;
 float in_b = * src ++ ;
 float out_r = mat . m [ 0 ] [ 0 ] * in_r + mat . m [ 1 ] [ 0 ] * in_g + mat . m [ 2 ] [ 0 ] * in_b + transform -> tx ;
 float out_g = mat . m [ 0 ] [ 1 ] * in_r + mat . m [ 1 ] [ 1 ] * in_g + mat . m [ 2 ] [ 1 ] * in_b + transform -> ty ;
 float out_b = mat . m [ 0 ] [ 2 ] * in_r + mat . m [ 1 ] [ 2 ] * in_g + mat . m [ 2 ] [ 2 ] * in_b + transform -> tz ;
 * dest ++ = clamp_float ( out_r ) ;
 * dest ++ = clamp_float ( out_g ) ;
 * dest ++ = clamp_float ( out_b ) ;
 }
 }