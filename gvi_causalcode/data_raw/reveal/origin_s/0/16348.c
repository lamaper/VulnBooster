void replace_dynstr_append_mem ( DYNAMIC_STRING * ds , const char * val , int len ) {
 char lower [ 512 ] ;


 char * c = lower ;
 for ( const char * v = val ;
 * v ;
 v ++ ) * c ++ = my_tolower ( charset_info , * v ) ;
 * c = '\0' ;
 val = lower ;
 }
 if ( glob_replace_regex ) {
 if ( ! multi_reg_replace ( glob_replace_regex , ( char * ) val ) ) {
 val = glob_replace_regex -> buf ;
 len = strlen ( val ) ;
 }
 }
 if ( glob_replace ) {
 replace_strings_append ( glob_replace , ds , val , len ) ;
 }
 else dynstr_append_mem ( ds , val , len ) ;
 }