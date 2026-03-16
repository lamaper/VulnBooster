static struct qcms_modular_transform * qcms_modular_transform_create_output ( qcms_profile * out ) {
 struct qcms_modular_transform * first_transform = NULL ;
 struct qcms_modular_transform * * next_transform = & first_transform ;
 if ( out -> B2A0 ) {
 struct qcms_modular_transform * lut_transform ;
 lut_transform = qcms_modular_transform_create_lut ( out -> B2A0 ) ;
 if ( ! lut_transform ) goto fail ;
 append_transform ( lut_transform , & next_transform ) ;
 }
 else if ( out -> mBA && out -> mBA -> num_in_channels == 3 && out -> mBA -> num_out_channels == 3 ) {
 struct qcms_modular_transform * lut_transform ;
 lut_transform = qcms_modular_transform_create_mAB ( out -> mBA ) ;
 if ( ! lut_transform ) goto fail ;
 append_transform ( lut_transform , & next_transform ) ;
 }
 else if ( out -> redTRC && out -> greenTRC && out -> blueTRC ) {
 struct qcms_modular_transform * transform ;
 transform = qcms_modular_transform_alloc ( ) ;
 if ( ! transform ) goto fail ;
 append_transform ( transform , & next_transform ) ;
 transform -> matrix = matrix_invert ( build_colorant_matrix ( out ) ) ;
 transform -> transform_module_fn = qcms_transform_module_matrix ;
 transform = qcms_modular_transform_alloc ( ) ;
 if ( ! transform ) goto fail ;
 append_transform ( transform , & next_transform ) ;
 transform -> matrix . m [ 0 ] [ 0 ] = 1.999969482421875f ;
 transform -> matrix . m [ 0 ] [ 1 ] = 0.f ;
 transform -> matrix . m [ 0 ] [ 2 ] = 0.f ;
 transform -> matrix . m [ 1 ] [ 0 ] = 0.f ;
 transform -> matrix . m [ 1 ] [ 1 ] = 1.999969482421875f ;
 transform -> matrix . m [ 1 ] [ 2 ] = 0.f ;
 transform -> matrix . m [ 2 ] [ 0 ] = 0.f ;
 transform -> matrix . m [ 2 ] [ 1 ] = 0.f ;
 transform -> matrix . m [ 2 ] [ 2 ] = 1.999969482421875f ;
 transform -> matrix . invalid = false ;
 transform -> transform_module_fn = qcms_transform_module_matrix ;
 transform = qcms_modular_transform_alloc ( ) ;
 if ( ! transform ) goto fail ;
 append_transform ( transform , & next_transform ) ;
 build_output_lut ( out -> redTRC , & transform -> output_gamma_lut_r , & transform -> output_gamma_lut_r_length ) ;
 build_output_lut ( out -> greenTRC , & transform -> output_gamma_lut_g , & transform -> output_gamma_lut_g_length ) ;
 build_output_lut ( out -> blueTRC , & transform -> output_gamma_lut_b , & transform -> output_gamma_lut_b_length ) ;
 transform -> transform_module_fn = qcms_transform_module_gamma_lut ;
 if ( ! transform -> output_gamma_lut_r || ! transform -> output_gamma_lut_g || ! transform -> output_gamma_lut_b ) {
 goto fail ;
 }
 }
 else {
 assert ( 0 && "Unsupported output profile workflow." ) ;
 return NULL ;
 }
 return first_transform ;
 fail : qcms_modular_transform_release ( first_transform ) ;
 return EMPTY_TRANSFORM_LIST ;
 }