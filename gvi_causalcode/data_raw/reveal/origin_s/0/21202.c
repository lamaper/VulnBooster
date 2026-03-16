static hb_bool_t hb_ucdn_decompose ( hb_unicode_funcs_t * ufuncs , hb_codepoint_t ab , hb_codepoint_t * a , hb_codepoint_t * b , void * user_data HB_UNUSED ) {
 return ucdn_decompose ( ab , a , b ) ;
 }