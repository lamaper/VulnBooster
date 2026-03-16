static inline void insert_dotted_circles ( const hb_ot_shape_plan_t * plan HB_UNUSED , hb_font_t * font , hb_buffer_t * buffer ) {
 bool has_broken_syllables = false ;
 unsigned int count = buffer -> len ;
 hb_glyph_info_t * info = buffer -> info ;
 for ( unsigned int i = 0 ;
 i < count ;
 i ++ ) if ( ( info [ i ] . syllable ( ) & 0x0F ) == broken_cluster ) {
 has_broken_syllables = true ;
 break ;
 }
 if ( likely ( ! has_broken_syllables ) ) return ;
 hb_codepoint_t dottedcircle_glyph ;
 if ( ! font -> get_glyph ( 0x25CCu , 0 , & dottedcircle_glyph ) ) return ;
 hb_glyph_info_t dottedcircle = {
 0 }
 ;
 dottedcircle . codepoint = 0x25CCu ;
 set_myanmar_properties ( dottedcircle ) ;
 dottedcircle . codepoint = dottedcircle_glyph ;
 buffer -> clear_output ( ) ;
 buffer -> idx = 0 ;
 unsigned int last_syllable = 0 ;
 while ( buffer -> idx < buffer -> len ) {
 unsigned int syllable = buffer -> cur ( ) . syllable ( ) ;
 syllable_type_t syllable_type = ( syllable_type_t ) ( syllable & 0x0F ) ;
 if ( unlikely ( last_syllable != syllable && syllable_type == broken_cluster ) ) {
 last_syllable = syllable ;
 hb_glyph_info_t info = dottedcircle ;
 info . cluster = buffer -> cur ( ) . cluster ;
 info . mask = buffer -> cur ( ) . mask ;
 info . syllable ( ) = buffer -> cur ( ) . syllable ( ) ;
 buffer -> output_info ( info ) ;
 }
 else buffer -> next_glyph ( ) ;
 }
 buffer -> swap_buffers ( ) ;
 }