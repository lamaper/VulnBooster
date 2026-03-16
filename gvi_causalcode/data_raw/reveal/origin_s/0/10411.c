static void * data_create_hangul ( const hb_ot_shape_plan_t * plan ) {
 hangul_shape_plan_t * hangul_plan = ( hangul_shape_plan_t * ) calloc ( 1 , sizeof ( hangul_shape_plan_t ) ) ;
 if ( unlikely ( ! hangul_plan ) ) return NULL ;
 for ( unsigned int i = 0 ;
 i < HANGUL_FEATURE_COUNT ;
 i ++ ) hangul_plan -> mask_array [ i ] = plan -> map . get_1_mask ( hangul_features [ i ] ) ;
 return hangul_plan ;
 }