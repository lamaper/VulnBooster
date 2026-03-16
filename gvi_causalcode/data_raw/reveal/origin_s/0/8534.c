void * data_create_arabic ( const hb_ot_shape_plan_t * plan ) {
 arabic_shape_plan_t * arabic_plan = ( arabic_shape_plan_t * ) calloc ( 1 , sizeof ( arabic_shape_plan_t ) ) ;
 if ( unlikely ( ! arabic_plan ) ) return NULL ;
 arabic_plan -> do_fallback = plan -> props . script == HB_SCRIPT_ARABIC ;
 for ( unsigned int i = 0 ;
 i < ARABIC_NUM_FEATURES ;
 i ++ ) {
 arabic_plan -> mask_array [ i ] = plan -> map . get_1_mask ( arabic_features [ i ] ) ;
 arabic_plan -> do_fallback = arabic_plan -> do_fallback && ( FEATURE_IS_SYRIAC ( arabic_features [ i ] ) || plan -> map . needs_fallback ( arabic_features [ i ] ) ) ;
 }
 return arabic_plan ;
 }