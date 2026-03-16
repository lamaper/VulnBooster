static void collect_features_indic ( hb_ot_shape_planner_t * plan ) {
 hb_ot_map_builder_t * map = & plan -> map ;
 map -> add_gsub_pause ( setup_syllables ) ;
 map -> add_global_bool_feature ( HB_TAG ( 'l' , 'o' , 'c' , 'l' ) ) ;
 map -> add_global_bool_feature ( HB_TAG ( 'c' , 'c' , 'm' , 'p' ) ) ;
 unsigned int i = 0 ;
 map -> add_gsub_pause ( initial_reordering ) ;
 for ( ;
 i < INDIC_BASIC_FEATURES ;
 i ++ ) {
 map -> add_feature ( indic_features [ i ] . tag , 1 , indic_features [ i ] . flags | F_MANUAL_ZWJ ) ;
 map -> add_gsub_pause ( NULL ) ;
 }
 map -> add_gsub_pause ( final_reordering ) ;
 for ( ;
 i < INDIC_NUM_FEATURES ;
 i ++ ) {
 map -> add_feature ( indic_features [ i ] . tag , 1 , indic_features [ i ] . flags | F_MANUAL_ZWJ ) ;
 }
 map -> add_global_bool_feature ( HB_TAG ( 'c' , 'a' , 'l' , 't' ) ) ;
 map -> add_global_bool_feature ( HB_TAG ( 'c' , 'l' , 'i' , 'g' ) ) ;
 map -> add_gsub_pause ( clear_syllables ) ;
 }