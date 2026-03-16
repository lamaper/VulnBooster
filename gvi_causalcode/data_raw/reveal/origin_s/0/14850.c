static void setup_masks_hangul ( const hb_ot_shape_plan_t * plan , hb_buffer_t * buffer , hb_font_t * font HB_UNUSED ) {
 const hangul_shape_plan_t * hangul_plan = ( const hangul_shape_plan_t * ) plan -> data ;
 if ( likely ( hangul_plan ) ) {
 unsigned int count = buffer -> len ;
 hb_glyph_info_t * info = buffer -> info ;
 for ( unsigned int i = 0 ;
 i < count ;
 i ++ , info ++ ) info -> mask |= hangul_plan -> mask_array [ info -> hangul_shaping_feature ( ) ] ;
 }
 HB_BUFFER_DEALLOCATE_VAR ( buffer , hangul_shaping_feature ) ;
 }