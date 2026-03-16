static void setup_masks_arabic ( const hb_ot_shape_plan_t * plan , hb_buffer_t * buffer , hb_font_t * font HB_UNUSED ) {
 HB_BUFFER_ALLOCATE_VAR ( buffer , arabic_shaping_action ) ;
 const arabic_shape_plan_t * arabic_plan = ( const arabic_shape_plan_t * ) plan -> data ;
 arabic_joining ( buffer ) ;
 if ( plan -> props . script == HB_SCRIPT_MONGOLIAN ) mongolian_variation_selectors ( buffer ) ;
 unsigned int count = buffer -> len ;
 hb_glyph_info_t * info = buffer -> info ;
 for ( unsigned int i = 0 ;
 i < count ;
 i ++ ) info [ i ] . mask |= arabic_plan -> mask_array [ info [ i ] . arabic_shaping_action ( ) ] ;
 HB_BUFFER_DEALLOCATE_VAR ( buffer , arabic_shaping_action ) ;
 }