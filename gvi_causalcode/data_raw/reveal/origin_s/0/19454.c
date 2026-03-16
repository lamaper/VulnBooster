static int compare_indic_order ( const hb_glyph_info_t * pa , const hb_glyph_info_t * pb ) {
 int a = pa -> indic_position ( ) ;
 int b = pb -> indic_position ( ) ;
 return a < b ? - 1 : a == b ? 0 : + 1 ;
 }