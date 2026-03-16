static inline unsigned int decompose_compatibility ( const hb_ot_shape_normalize_context_t * c , hb_codepoint_t u ) {
 unsigned int len , i ;
 hb_codepoint_t decomposed [ HB_UNICODE_MAX_DECOMPOSITION_LEN ] ;
 hb_codepoint_t glyphs [ HB_UNICODE_MAX_DECOMPOSITION_LEN ] ;
 len = c -> buffer -> unicode -> decompose_compatibility ( u , decomposed ) ;
 if ( ! len ) return 0 ;
 for ( i = 0 ;
 i < len ;
 i ++ ) if ( ! c -> font -> get_glyph ( decomposed [ i ] , 0 , & glyphs [ i ] ) ) return 0 ;
 for ( i = 0 ;
 i < len ;
 i ++ ) output_char ( c -> buffer , decomposed [ i ] , glyphs [ i ] ) ;
 return len ;
 }