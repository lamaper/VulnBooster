static void * data_create_indic ( const hb_ot_shape_plan_t * plan ) {
 indic_shape_plan_t * indic_plan = ( indic_shape_plan_t * ) calloc ( 1 , sizeof ( indic_shape_plan_t ) ) ;
 if ( unlikely ( ! indic_plan ) ) return NULL ;
 indic_plan -> config = & indic_configs [ 0 ] ;
 for ( unsigned int i = 1 ;
 i < ARRAY_LENGTH ( indic_configs ) ;
 i ++ ) if ( plan -> props . script == indic_configs [ i ] . script ) {
 indic_plan -> config = & indic_configs [ i ] ;
 break ;
 }
 indic_plan -> is_old_spec = indic_plan -> config -> has_old_spec && ( ( plan -> map . chosen_script [ 0 ] & 0x000000FFu ) != '2' ) ;
 indic_plan -> virama_glyph = ( hb_codepoint_t ) - 1 ;
 bool zero_context = ! indic_plan -> is_old_spec ;
 indic_plan -> rphf . init ( & plan -> map , HB_TAG ( 'r' , 'p' , 'h' , 'f' ) , zero_context ) ;
 indic_plan -> pref . init ( & plan -> map , HB_TAG ( 'p' , 'r' , 'e' , 'f' ) , zero_context ) ;
 indic_plan -> blwf . init ( & plan -> map , HB_TAG ( 'b' , 'l' , 'w' , 'f' ) , zero_context ) ;
 indic_plan -> pstf . init ( & plan -> map , HB_TAG ( 'p' , 's' , 't' , 'f' ) , zero_context ) ;
 for ( unsigned int i = 0 ;
 i < ARRAY_LENGTH ( indic_plan -> mask_array ) ;
 i ++ ) indic_plan -> mask_array [ i ] = ( indic_features [ i ] . flags & F_GLOBAL ) ? : plan -> map . get_1_mask ( indic_features [ i ] . tag ) ;
 return indic_plan ;
 }