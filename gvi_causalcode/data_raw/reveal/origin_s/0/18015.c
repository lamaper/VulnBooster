void hb_font_funcs_destroy ( hb_font_funcs_t * ffuncs ) {
 if ( ! hb_object_destroy ( ffuncs ) ) return ;

 HB_FONT_FUNCS_IMPLEMENT_CALLBACKS # undef HB_FONT_FUNC_IMPLEMENT free ( ffuncs ) ;
 }