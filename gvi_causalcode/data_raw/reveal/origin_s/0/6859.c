static inline void decompose_multi_char_cluster ( const hb_ot_shape_normalize_context_t * c , unsigned int end , bool short_circuit ) {
 hb_buffer_t * const buffer = c -> buffer ;
 for ( unsigned int i = buffer -> idx ;
 i < end ;
 i ++ ) if ( unlikely ( buffer -> unicode -> is_variation_selector ( buffer -> info [ i ] . codepoint ) ) ) {
 handle_variation_selector_cluster ( c , end , short_circuit ) ;
 return ;
 }
 while ( buffer -> idx < end ) decompose_current_character ( c , short_circuit ) ;
 }