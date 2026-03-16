static int compare_myanmar_order ( const hb_glyph_info_t * pa , const hb_glyph_info_t * pb ) {
 int a = pa -> myanmar_position ( ) ;
 int b = pb -> myanmar_position ( ) ;
 return a < b ? - 1 : a == b ? 0 : + 1 ;
 }