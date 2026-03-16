static unsigned int hb_ucdn_eastasian_width ( hb_unicode_funcs_t * ufuncs , hb_codepoint_t unicode , void * user_data HB_UNUSED ) {
 int w = ucdn_get_east_asian_width ( unicode ) ;
 return ( w == UCDN_EAST_ASIAN_F || w == UCDN_EAST_ASIAN_W ) ? 2 : 1 ;
 }