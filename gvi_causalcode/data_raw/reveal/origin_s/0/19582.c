hb_font_funcs_t * hb_font_funcs_create ( void ) {
 hb_font_funcs_t * ffuncs ;
 if ( ! ( ffuncs = hb_object_create < hb_font_funcs_t > ( ) ) ) return hb_font_funcs_get_empty ( ) ;
 ffuncs -> get = _hb_font_funcs_nil . get ;
 return ffuncs ;
 }