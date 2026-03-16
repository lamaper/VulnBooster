static struct qcms_modular_transform * qcms_modular_transform_create_mAB ( struct lutmABType * lut ) {
 struct qcms_modular_transform * first_transform = NULL ;
 struct qcms_modular_transform * * next_transform = & first_transform ;
 struct qcms_modular_transform * transform = NULL ;
 if ( lut -> a_curves [ 0 ] != NULL ) {
 size_t clut_length ;
 float * clut ;
 if ( ! lut -> clut_table ) goto fail ;
 transform = qcms_modular_transform_alloc ( ) ;
 if ( ! transform ) goto fail ;
 append_transform ( transform , & next_transform ) ;
 transform -> input_clut_table_r = build_input_gamma_table ( lut -> a_curves [ 0 ] ) ;
 transform -> input_clut_table_g = build_input_gamma_table ( lut -> a_curves [ 1 ] ) ;
 transform -> input_clut_table_b = build_input_gamma_table ( lut -> a_curves [ 2 ] ) ;
 transform -> transform_module_fn = qcms_transform_module_gamma_table ;
 if ( lut -> num_grid_points [ 0 ] != lut -> num_grid_points [ 1 ] || lut -> num_grid_points [ 1 ] != lut -> num_grid_points [ 2 ] ) {
 goto fail ;
 }
 transform = qcms_modular_transform_alloc ( ) ;
 if ( ! transform ) goto fail ;
 append_transform ( transform , & next_transform ) ;
 clut_length = sizeof ( float ) * pow ( lut -> num_grid_points [ 0 ] , 3 ) * 3 ;
 clut = malloc ( clut_length ) ;
 if ( ! clut ) goto fail ;
 memcpy ( clut , lut -> clut_table , clut_length ) ;
 transform -> r_clut = clut + 0 ;
 transform -> g_clut = clut + 1 ;
 transform -> b_clut = clut + 2 ;
 transform -> grid_size = lut -> num_grid_points [ 0 ] ;
 transform -> transform_module_fn = qcms_transform_module_clut_only ;
 }
 if ( lut -> m_curves [ 0 ] != NULL ) {
 transform = qcms_modular_transform_alloc ( ) ;
 if ( ! transform ) goto fail ;
 append_transform ( transform , & next_transform ) ;
 transform -> input_clut_table_r = build_input_gamma_table ( lut -> m_curves [ 0 ] ) ;
 transform -> input_clut_table_g = build_input_gamma_table ( lut -> m_curves [ 1 ] ) ;
 transform -> input_clut_table_b = build_input_gamma_table ( lut -> m_curves [ 2 ] ) ;
 transform -> transform_module_fn = qcms_transform_module_gamma_table ;
 transform = qcms_modular_transform_alloc ( ) ;
 if ( ! transform ) goto fail ;
 append_transform ( transform , & next_transform ) ;
 transform -> matrix = build_mAB_matrix ( lut ) ;
 if ( transform -> matrix . invalid ) goto fail ;
 transform -> tx = s15Fixed16Number_to_float ( lut -> e03 ) ;
 transform -> ty = s15Fixed16Number_to_float ( lut -> e13 ) ;
 transform -> tz = s15Fixed16Number_to_float ( lut -> e23 ) ;
 transform -> transform_module_fn = qcms_transform_module_matrix_translate ;
 }
 if ( lut -> b_curves [ 0 ] != NULL ) {
 transform = qcms_modular_transform_alloc ( ) ;
 if ( ! transform ) goto fail ;
 append_transform ( transform , & next_transform ) ;
 transform -> input_clut_table_r = build_input_gamma_table ( lut -> b_curves [ 0 ] ) ;
 transform -> input_clut_table_g = build_input_gamma_table ( lut -> b_curves [ 1 ] ) ;
 transform -> input_clut_table_b = build_input_gamma_table ( lut -> b_curves [ 2 ] ) ;
 transform -> transform_module_fn = qcms_transform_module_gamma_table ;
 }
 else {
 goto fail ;
 }
 if ( lut -> reversed ) {
 first_transform = reverse_transform ( first_transform ) ;
 }
 return first_transform ;
 fail : qcms_modular_transform_release ( first_transform ) ;
 return NULL ;
 }