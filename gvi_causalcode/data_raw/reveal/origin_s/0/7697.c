static hb_unicode_general_category_t hb_ucdn_general_category ( hb_unicode_funcs_t * ufuncs , hb_codepoint_t unicode , void * user_data HB_UNUSED ) {
 return ( hb_unicode_general_category_t ) ucdn_get_general_category ( unicode ) ;
 }