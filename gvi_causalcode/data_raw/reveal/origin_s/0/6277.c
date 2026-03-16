static hb_codepoint_t hb_ucdn_mirroring ( hb_unicode_funcs_t * ufuncs , hb_codepoint_t unicode , void * user_data HB_UNUSED ) {
 return ucdn_mirror ( unicode ) ;
 }