static bool decompose_indic ( const hb_ot_shape_normalize_context_t * c , hb_codepoint_t ab , hb_codepoint_t * a , hb_codepoint_t * b ) {
 switch ( ab ) {
 case 0x0931u : return false ;
 case 0x0B94u : return false ;
 case 0x0F77u : * a = 0x0FB2u ;
 * b = 0x0F81u ;
 return true ;
 case 0x0F79u : * a = 0x0FB3u ;
 * b = 0x0F81u ;
 return true ;
 case 0x17BEu : * a = 0x17C1u ;
 * b = 0x17BEu ;
 return true ;
 case 0x17BFu : * a = 0x17C1u ;
 * b = 0x17BFu ;
 return true ;
 case 0x17C0u : * a = 0x17C1u ;
 * b = 0x17C0u ;
 return true ;
 case 0x17C4u : * a = 0x17C1u ;
 * b = 0x17C4u ;
 return true ;
 case 0x17C5u : * a = 0x17C1u ;
 * b = 0x17C5u ;
 return true ;
 case 0x1925u : * a = 0x1920u ;
 * b = 0x1923u ;
 return true ;
 case 0x1926u : * a = 0x1920u ;
 * b = 0x1924u ;
 return true ;
 case 0x1B3Cu : * a = 0x1B42u ;
 * b = 0x1B3Cu ;
 return true ;
 case 0x1112Eu : * a = 0x11127u ;
 * b = 0x11131u ;
 return true ;
 case 0x1112Fu : * a = 0x11127u ;
 * b = 0x11132u ;
 return true ;

 return true ;
 case 0x1C29u : * a = no decomp , -> LEFT ;
 return true ;
 case 0xA9C0u : * a = no decomp , -> RIGHT ;
 return true ;
 case 0x111BuF : * a = no decomp , -> ABOVE ;
 return true ;

 if ( ( ab == 0x0DDAu || hb_in_range ( ab , 0x0DDCu , 0x0DDEu ) ) ) {
 const indic_shape_plan_t * indic_plan = ( const indic_shape_plan_t * ) c -> plan -> data ;
 hb_codepoint_t glyph ;
 if ( hb_options ( ) . uniscribe_bug_compatible || ( c -> font -> get_glyph ( ab , 0 , & glyph ) && indic_plan -> pstf . would_substitute ( & glyph , 1 , c -> font -> face ) ) ) {
 * a = 0x0DD9u ;
 * b = ab ;
 return true ;
 }
 }
 return c -> unicode -> decompose ( ab , a , b ) ;
 }