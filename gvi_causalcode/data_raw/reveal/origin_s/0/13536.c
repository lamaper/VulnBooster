UScriptCode hb_icu_script_from_script ( hb_script_t script ) {
 if ( unlikely ( script == HB_SCRIPT_INVALID ) ) return USCRIPT_INVALID_CODE ;
 for ( unsigned int i = 0 ;
 i < USCRIPT_CODE_LIMIT ;
 i ++ ) if ( unlikely ( hb_icu_script_to_script ( ( UScriptCode ) i ) == script ) ) return ( UScriptCode ) i ;
 return USCRIPT_UNKNOWN ;
 }