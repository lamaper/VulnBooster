static bool decompose_unicode ( const hb_ot_shape_normalize_context_t * c , hb_codepoint_t ab , hb_codepoint_t * a , hb_codepoint_t * b ) {
 return c -> unicode -> decompose ( ab , a , b ) ;
 }