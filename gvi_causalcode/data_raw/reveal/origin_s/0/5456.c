static unsigned int hb_ucdn_decompose_compatibility ( hb_unicode_funcs_t * ufuncs , hb_codepoint_t u , hb_codepoint_t * decomposed , void * user_data HB_UNUSED ) {
 return ucdn_compat_decompose ( u , decomposed ) ;
 }