hb_tag_t hb_ot_tag_from_language ( hb_language_t language ) {
 const char * lang_str , * s ;
 if ( language == HB_LANGUAGE_INVALID ) return HB_OT_TAG_DEFAULT_LANGUAGE ;
 lang_str = hb_language_to_string ( language ) ;
 s = strstr ( lang_str , "x-hbot" ) ;
 if ( s ) {
 char tag [ 4 ] ;
 int i ;
 s += 6 ;
 for ( i = 0 ;
 i < 4 && ISALPHA ( s [ i ] ) ;
 i ++ ) tag [ i ] = TOUPPER ( s [ i ] ) ;
 if ( i ) {
 for ( ;
 i < 4 ;
 i ++ ) tag [ i ] = ' ' ;
 return HB_TAG_CHAR4 ( tag ) ;
 }
 }
 {
 const LangTag * lang_tag ;
 lang_tag = ( LangTag * ) bsearch ( lang_str , ot_languages , ARRAY_LENGTH ( ot_languages ) , sizeof ( LangTag ) , ( hb_compare_func_t ) lang_compare_first_component ) ;
 if ( lang_tag ) return lang_tag -> tag ;
 }
 if ( 0 == lang_compare_first_component ( lang_str , "zh" ) ) {
 unsigned int i ;
 for ( i = 0 ;
 i < ARRAY_LENGTH ( ot_languages_zh ) ;
 i ++ ) {
 const LangTagLong * lang_tag ;
 lang_tag = & ot_languages_zh [ i ] ;
 if ( lang_matches ( lang_str , lang_tag -> language ) ) return lang_tag -> tag ;
 }
 return HB_TAG ( 'Z' , 'H' , 'S' , ' ' ) ;
 }
 s = strchr ( lang_str , '-' ) ;
 if ( ! s ) s = lang_str + strlen ( lang_str ) ;
 if ( s - lang_str == 3 ) {
 return hb_tag_from_string ( lang_str , s - lang_str ) & ~ 0x20202000u ;
 }
 return HB_OT_TAG_DEFAULT_LANGUAGE ;
 }