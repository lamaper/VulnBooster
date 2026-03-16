static hb_script_t hb_icu_unicode_script ( hb_unicode_funcs_t * ufuncs HB_UNUSED , hb_codepoint_t unicode , void * user_data HB_UNUSED ) {
 UErrorCode status = U_ZERO_ERROR ;
 UScriptCode scriptCode = uscript_getScript ( unicode , & status ) ;
 if ( unlikely ( U_FAILURE ( status ) ) ) return HB_SCRIPT_UNKNOWN ;
 return hb_icu_script_to_script ( scriptCode ) ;
 }