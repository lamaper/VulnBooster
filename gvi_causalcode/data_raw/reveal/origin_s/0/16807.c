static unsigned int hb_icu_unicode_eastasian_width ( hb_unicode_funcs_t * ufuncs HB_UNUSED , hb_codepoint_t unicode , void * user_data HB_UNUSED ) {
 switch ( u_getIntPropertyValue ( unicode , UCHAR_EAST_ASIAN_WIDTH ) ) {
 case U_EA_WIDE : case U_EA_FULLWIDTH : return 2 ;
 case U_EA_NEUTRAL : case U_EA_AMBIGUOUS : case U_EA_HALFWIDTH : case U_EA_NARROW : return 1 ;
 }
 return 1 ;
 }