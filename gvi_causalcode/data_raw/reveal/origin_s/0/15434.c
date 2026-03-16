static bool compose_indic ( const hb_ot_shape_normalize_context_t * c , hb_codepoint_t a , hb_codepoint_t b , hb_codepoint_t * ab ) {
 if ( HB_UNICODE_GENERAL_CATEGORY_IS_MARK ( c -> unicode -> general_category ( a ) ) ) return false ;
 if ( a == 0x09AFu && b == 0x09BCu ) {
 * ab = 0x09DFu ;
 return true ;
 }
 return c -> unicode -> compose ( a , b , ab ) ;
 }