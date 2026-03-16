struct qcms_modular_transform * qcms_modular_transform_create_input ( qcms_profile * in ) {
 struct qcms_modular_transform * first_transform = NULL ;
 struct qcms_modular_transform * * next_transform = & first_transform ;
 if ( in -> A2B0 ) {
 struct qcms_modular_transform * lut_transform ;
 lut_transform = qcms_modular_transform_create_lut ( in -> A2B0 ) ;
 if ( ! lut_transform ) goto fail ;
 append_transform ( lut_transform , & next_transform ) ;
 }
 else if ( in -> mAB && in -> mAB -> num_in_channels == 3 && in -> mAB -> num_out_channels == 3 ) {
 struct qcms_modular_transform * mAB_transform ;
 mAB_transform = qcms_modular_transform_create_mAB ( in -> mAB ) ;
 if ( ! mAB_transform ) goto fail ;
 append_transform ( mAB_transform , & next_transform ) ;
 }
 else {
 struct qcms_modular_transform * transform ;
 transform = qcms_modular_transform_alloc ( ) ;
 if ( ! transform ) goto fail ;
 append_transform ( transform , & next_transform ) ;
 transform -> input_clut_table_r = build_input_gamma_table ( in -> redTRC ) ;
 transform -> input_clut_table_g = build_input_gamma_table ( in -> greenTRC ) ;
 transform -> input_clut_table_b = build_input_gamma_table ( in -> blueTRC ) ;
 transform -> transform_module_fn = qcms_transform_module_gamma_table ;
 if ( ! transform -> input_clut_table_r || ! transform -> input_clut_table_g || ! transform -> input_clut_table_b ) {
 goto fail ;
 }
 transform = qcms_modular_transform_alloc ( ) ;
 if ( ! transform ) goto fail ;
 append_transform ( transform , & next_transform ) ;
 transform -> matrix . m [ 0 ] [ 0 ] = 1 / 1.999969482421875f ;
 transform -> matrix . m [ 0 ] [ 1 ] = 0.f ;
 transform -> matrix . m [ 0 ] [ 2 ] = 0.f ;
 transform -> matrix . m [ 1 ] [ 0 ] = 0.f ;
 transform -> matrix . m [ 1 ] [ 1 ] = 1 / 1.999969482421875f ;
 transform -> matrix . m [ 1 ] [ 2 ] = 0.f ;
 transform -> matrix . m [ 2 ] [ 0 ] = 0.f ;
 transform -> matrix . m [ 2 ] [ 1 ] = 0.f ;
 transform -> matrix . m [ 2 ] [ 2 ] = 1 / 1.999969482421875f ;
 transform -> matrix . invalid = false ;
 transform -> transform_module_fn = qcms_transform_module_matrix ;
 transform = qcms_modular_transform_alloc ( ) ;
 if ( ! transform ) goto fail ;
 append_transform ( transform , & next_transform ) ;
 transform -> matrix = build_colorant_matrix ( in ) ;
 transform -> transform_module_fn = qcms_transform_module_matrix ;
 }
 return first_transform ;
 fail : qcms_modular_transform_release ( first_transform ) ;
 return EMPTY_TRANSFORM_LIST ;
 }