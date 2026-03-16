static GRANT_NAME * name_hash_search ( HASH * name_hash , const char * host , const char * ip , const char * db , const char * user , const char * tname , bool exact , bool name_tolower ) {
 char helping [ NAME_LEN * 2 + USERNAME_LENGTH + 3 ] , * name_ptr ;
 uint len ;
 GRANT_NAME * grant_name , * found = 0 ;
 HASH_SEARCH_STATE state ;
 name_ptr = strmov ( strmov ( helping , user ) + 1 , db ) + 1 ;
 len = ( uint ) ( strmov ( name_ptr , tname ) - helping ) + 1 ;
 if ( name_tolower ) my_casedn_str ( files_charset_info , name_ptr ) ;
 for ( grant_name = ( GRANT_NAME * ) hash_first ( name_hash , ( uchar * ) helping , len , & state ) ;
 grant_name ;
 grant_name = ( GRANT_NAME * ) hash_next ( name_hash , ( uchar * ) helping , len , & state ) ) {
 if ( exact ) {
 if ( ! grant_name -> host . hostname || ( host && ! my_strcasecmp ( system_charset_info , host , grant_name -> host . hostname ) ) || ( ip && ! strcmp ( ip , grant_name -> host . hostname ) ) ) return grant_name ;
 }
 else {
 if ( compare_hostname ( & grant_name -> host , host , ip ) && ( ! found || found -> sort < grant_name -> sort ) ) found = grant_name ;
 }
 }
 return found ;
 }