static hb_bool_t hb_ucdn_compose ( hb_unicode_funcs_t * ufuncs , hb_codepoint_t a , hb_codepoint_t b , hb_codepoint_t * ab , void * user_data HB_UNUSED ) {
 return ucdn_compose ( ab , a , b ) ;
 }