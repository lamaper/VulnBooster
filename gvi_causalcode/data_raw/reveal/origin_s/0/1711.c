void check_eol_junk ( const char * eol ) {
 const char * p = eol ;
 DBUG_ENTER ( "check_eol_junk" ) ;
 DBUG_PRINT ( "enter" , ( "eol: %s" , eol ) ) ;
 while ( * p && ( my_isspace ( charset_info , * p ) || * p == '#' || * p == '\n' ) ) {
 if ( * p && * p == '#' ) {
 p ++ ;
 while ( * p && * p != '\n' ) p ++ ;
 }
 if ( * p && * p == '\n' ) check_eol_junk_line ( p ) ;
 if ( * p ) p ++ ;
 }
 check_eol_junk_line ( p ) ;
 DBUG_VOID_RETURN ;
 }