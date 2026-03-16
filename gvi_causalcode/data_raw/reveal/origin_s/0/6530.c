void hb_font_funcs_make_immutable ( hb_font_funcs_t * ffuncs ) {
 if ( unlikely ( hb_object_is_inert ( ffuncs ) ) ) return ;
 ffuncs -> immutable = true ;
 }