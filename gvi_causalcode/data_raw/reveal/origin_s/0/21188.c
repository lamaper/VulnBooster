static void collect_features_hangul ( hb_ot_shape_planner_t * plan ) {
 hb_ot_map_builder_t * map = & plan -> map ;
 for ( unsigned int i = FIRST_HANGUL_FEATURE ;
 i < HANGUL_FEATURE_COUNT ;
 i ++ ) map -> add_feature ( hangul_features [ i ] , 1 , F_NONE ) ;
 }