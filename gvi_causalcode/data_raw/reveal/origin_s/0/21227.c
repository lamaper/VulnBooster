static hb_script_t hb_ucdn_script ( hb_unicode_funcs_t * ufuncs , hb_codepoint_t unicode , void * user_data HB_UNUSED ) {
 return ucdn_script_translate [ ucdn_get_script ( unicode ) ] ;
 }