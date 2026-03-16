static bool compose_unicode ( const hb_ot_shape_normalize_context_t * c , hb_codepoint_t a , hb_codepoint_t b , hb_codepoint_t * ab ) {
 return c -> unicode -> compose ( a , b , ab ) ;
 }