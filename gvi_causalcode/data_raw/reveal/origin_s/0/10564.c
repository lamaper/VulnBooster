static void update_consonant_positions ( const hb_ot_shape_plan_t * plan , hb_font_t * font , hb_buffer_t * buffer ) {
 const indic_shape_plan_t * indic_plan = ( const indic_shape_plan_t * ) plan -> data ;
 if ( indic_plan -> config -> base_pos != BASE_POS_LAST ) return ;
 hb_codepoint_t virama ;
 if ( indic_plan -> get_virama_glyph ( font , & virama ) ) {
 hb_face_t * face = font -> face ;
 unsigned int count = buffer -> len ;
 hb_glyph_info_t * info = buffer -> info ;
 for ( unsigned int i = 0 ;
 i < count ;
 i ++ ) if ( info [ i ] . indic_position ( ) == POS_BASE_C ) {
 hb_codepoint_t consonant = info [ i ] . codepoint ;
 info [ i ] . indic_position ( ) = consonant_position_from_face ( indic_plan , consonant , virama , face ) ;
 }
 }
 }