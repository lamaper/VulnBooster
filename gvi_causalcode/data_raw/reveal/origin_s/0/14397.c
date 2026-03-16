static int compare_combining_class ( const hb_glyph_info_t * pa , const hb_glyph_info_t * pb ) {
 unsigned int a = _hb_glyph_info_get_modified_combining_class ( pa ) ;
 unsigned int b = _hb_glyph_info_get_modified_combining_class ( pb ) ;
 return a < b ? - 1 : a == b ? 0 : + 1 ;
 }