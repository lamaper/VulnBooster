static hb_unicode_combining_class_t hb_icu_unicode_combining_class ( hb_unicode_funcs_t * ufuncs HB_UNUSED , hb_codepoint_t unicode , void * user_data HB_UNUSED ) {
 return ( hb_unicode_combining_class_t ) u_getCombiningClass ( unicode ) ;
 }