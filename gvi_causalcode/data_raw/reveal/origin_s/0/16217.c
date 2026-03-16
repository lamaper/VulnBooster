static void override_features_indic ( hb_ot_shape_planner_t * plan ) {
 if ( hb_options ( ) . uniscribe_bug_compatible ) {
 switch ( ( hb_tag_t ) plan -> props . script ) {
 case HB_SCRIPT_KHMER : plan -> map . add_feature ( HB_TAG ( 'k' , 'e' , 'r' , 'n' ) , 0 , F_GLOBAL ) ;
 break ;
 }
 }
 plan -> map . add_feature ( HB_TAG ( 'l' , 'i' , 'g' , 'a' ) , 0 , F_GLOBAL ) ;
 }