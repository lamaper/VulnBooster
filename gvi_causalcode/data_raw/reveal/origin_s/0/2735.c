static hb_unicode_combining_class_t hb_ucdn_combining_class ( hb_unicode_funcs_t * ufuncs , hb_codepoint_t unicode , void * user_data HB_UNUSED ) {
 return ( hb_unicode_combining_class_t ) ucdn_get_combining_class ( unicode ) ;
 }