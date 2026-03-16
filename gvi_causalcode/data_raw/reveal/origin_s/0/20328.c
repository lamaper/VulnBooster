static void collect_features_myanmar ( hb_ot_shape_planner_t * plan ) {
 hb_ot_map_builder_t * map = & plan -> map ;
 map -> add_gsub_pause ( setup_syllables ) ;
 map -> add_global_bool_feature ( HB_TAG ( 'l' , 'o' , 'c' , 'l' ) ) ;
 map -> add_global_bool_feature ( HB_TAG ( 'c' , 'c' , 'm' , 'p' ) ) ;
 map -> add_gsub_pause ( initial_reordering ) ;
 for ( unsigned int i = 0 ;
 i < ARRAY_LENGTH ( basic_features ) ;
 i ++ ) {
 map -> add_feature ( basic_features [ i ] , 1 , F_GLOBAL | F_MANUAL_ZWJ ) ;
 map -> add_gsub_pause ( NULL ) ;
 }
 map -> add_gsub_pause ( final_reordering ) ;
 for ( unsigned int i = 0 ;
 i < ARRAY_LENGTH ( other_features ) ;
 i ++ ) map -> add_feature ( other_features [ i ] , 1 , F_GLOBAL | F_MANUAL_ZWJ ) ;
 }