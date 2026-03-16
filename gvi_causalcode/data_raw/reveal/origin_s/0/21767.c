static my_bool test_if_special_chars ( const char * str ) {

 * str ;
 str ++ ) if ( ! my_isvar ( charset_info , * str ) && * str != '$' ) return 1 ;

 }