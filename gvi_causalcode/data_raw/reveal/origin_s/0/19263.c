static void collect_features_arabic ( hb_ot_shape_planner_t * plan ) {
 hb_ot_map_builder_t * map = & plan -> map ;
 map -> add_gsub_pause ( nuke_joiners ) ;
 map -> add_global_bool_feature ( HB_TAG ( 'c' , 'c' , 'm' , 'p' ) ) ;
 map -> add_global_bool_feature ( HB_TAG ( 'l' , 'o' , 'c' , 'l' ) ) ;
 map -> add_gsub_pause ( NULL ) ;
 for ( unsigned int i = 0 ;
 i < ARABIC_NUM_FEATURES ;
 i ++ ) {
 bool has_fallback = plan -> props . script == HB_SCRIPT_ARABIC && ! FEATURE_IS_SYRIAC ( arabic_features [ i ] ) ;
 map -> add_feature ( arabic_features [ i ] , 1 , has_fallback ? F_HAS_FALLBACK : F_NONE ) ;
 map -> add_gsub_pause ( NULL ) ;
 }
 map -> add_feature ( HB_TAG ( 'r' , 'l' , 'i' , 'g' ) , 1 , F_GLOBAL | F_HAS_FALLBACK ) ;
 if ( plan -> props . script == HB_SCRIPT_ARABIC ) map -> add_gsub_pause ( arabic_fallback_shape ) ;
 map -> add_global_bool_feature ( HB_TAG ( 'c' , 'a' , 'l' , 't' ) ) ;
 map -> add_gsub_pause ( NULL ) ;
 map -> add_global_bool_feature ( HB_TAG ( 'm' , 's' , 'e' , 't' ) ) ;
 }