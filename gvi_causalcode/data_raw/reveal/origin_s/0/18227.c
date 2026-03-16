static struct qcms_modular_transform * qcms_modular_transform_create ( qcms_profile * in , qcms_profile * out ) {
 struct qcms_modular_transform * first_transform = NULL ;
 struct qcms_modular_transform * * next_transform = & first_transform ;
 if ( in -> color_space == RGB_SIGNATURE ) {
 struct qcms_modular_transform * rgb_to_pcs ;
 rgb_to_pcs = qcms_modular_transform_create_input ( in ) ;
 if ( ! rgb_to_pcs ) goto fail ;
 append_transform ( rgb_to_pcs , & next_transform ) ;
 }
 else {
 assert ( 0 && "input color space not supported" ) ;
 goto fail ;
 }
 if ( in -> pcs == LAB_SIGNATURE && out -> pcs == XYZ_SIGNATURE ) {
 struct qcms_modular_transform * lab_to_pcs ;
 lab_to_pcs = qcms_modular_transform_alloc ( ) ;
 if ( ! lab_to_pcs ) goto fail ;
 append_transform ( lab_to_pcs , & next_transform ) ;
 lab_to_pcs -> transform_module_fn = qcms_transform_module_LAB_to_XYZ ;
 }
 if ( in -> pcs == XYZ_SIGNATURE && out -> pcs == LAB_SIGNATURE ) {
 struct qcms_modular_transform * pcs_to_lab ;
 pcs_to_lab = qcms_modular_transform_alloc ( ) ;
 if ( ! pcs_to_lab ) goto fail ;
 append_transform ( pcs_to_lab , & next_transform ) ;
 pcs_to_lab -> transform_module_fn = qcms_transform_module_XYZ_to_LAB ;
 }
 if ( out -> color_space == RGB_SIGNATURE ) {
 struct qcms_modular_transform * pcs_to_rgb ;
 pcs_to_rgb = qcms_modular_transform_create_output ( out ) ;
 if ( ! pcs_to_rgb ) goto fail ;
 append_transform ( pcs_to_rgb , & next_transform ) ;
 }
 else {
 assert ( 0 && "output color space not supported" ) ;
 goto fail ;
 }
 return first_transform ;
 fail : qcms_modular_transform_release ( first_transform ) ;
 return EMPTY_TRANSFORM_LIST ;
 }