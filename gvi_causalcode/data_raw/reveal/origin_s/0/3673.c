static hb_codepoint_t hb_icu_unicode_mirroring ( hb_unicode_funcs_t * ufuncs HB_UNUSED , hb_codepoint_t unicode , void * user_data HB_UNUSED ) {
 return u_charMirror ( unicode ) ;
 }