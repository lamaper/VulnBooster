static inline unsigned int decompose ( const hb_ot_shape_normalize_context_t * c , bool shortest , hb_codepoint_t ab ) {
 hb_codepoint_t a , b , a_glyph , b_glyph ;
 hb_buffer_t * const buffer = c -> buffer ;
 hb_font_t * const font = c -> font ;
 if ( ! c -> decompose ( c , ab , & a , & b ) || ( b && ! font -> get_glyph ( b , 0 , & b_glyph ) ) ) return 0 ;
 bool has_a = font -> get_glyph ( a , 0 , & a_glyph ) ;
 if ( shortest && has_a ) {
 output_char ( buffer , a , a_glyph ) ;
 if ( likely ( b ) ) {
 output_char ( buffer , b , b_glyph ) ;
 return 2 ;
 }
 return 1 ;
 }
 unsigned int ret ;
 if ( ( ret = decompose ( c , shortest , a ) ) ) {
 if ( b ) {
 output_char ( buffer , b , b_glyph ) ;
 return ret + 1 ;
 }
 return ret ;
 }
 if ( has_a ) {
 output_char ( buffer , a , a_glyph ) ;
 if ( likely ( b ) ) {
 output_char ( buffer , b , b_glyph ) ;
 return 2 ;
 }
 return 1 ;
 }
 return 0 ;
 }