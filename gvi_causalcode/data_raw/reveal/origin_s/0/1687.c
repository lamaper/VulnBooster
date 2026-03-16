static void setup_masks_myanmar ( const hb_ot_shape_plan_t * plan HB_UNUSED , hb_buffer_t * buffer , hb_font_t * font HB_UNUSED ) {
 HB_BUFFER_ALLOCATE_VAR ( buffer , myanmar_category ) ;
 HB_BUFFER_ALLOCATE_VAR ( buffer , myanmar_position ) ;
 unsigned int count = buffer -> len ;
 hb_glyph_info_t * info = buffer -> info ;
 for ( unsigned int i = 0 ;
 i < count ;
 i ++ ) set_myanmar_properties ( info [ i ] ) ;
 }